#include <stdio.h>
#include <stdlib.h>

#include "../src/queue.h"

#define ASSERT_TRUE(expr)                                      \
do {                                                           \
    if (!(expr)) {                                             \
        printf("[FAIL] %s:%d -> %s\n",                         \
               __FILE__, __LINE__, #expr);                     \
        exit(EXIT_FAILURE);                                    \
    }                                                          \
} while (0)

#define ASSERT_EQ(expected, actual)                            \
do {                                                           \
    if ((expected) != (actual)) {                              \
        printf("[FAIL] %s:%d\n",                               \
               __FILE__, __LINE__);                            \
        printf("Expected %d, got %d\n",                        \
               (expected), (actual));                          \
        exit(EXIT_FAILURE);                                    \
    }                                                          \
} while (0)


static void test_init(void)
{
    queue* q = queue_init();

    ASSERT_TRUE(q != NULL);
    ASSERT_TRUE(queue_empty(q));

    ASSERT_EQ(0, q->head);
    ASSERT_EQ(0, q->vec->size);

    queue_free(q);

    printf("[PASS] test_init\n");
}

static void test_enqueue_single(void)
{
    queue* q = queue_init();

    queue_enqueue(q, 42);

    ASSERT_TRUE(!queue_empty(q));
    ASSERT_EQ(42, queue_front(q));

    queue_free(q);

    printf("[PASS] test_enqueue_single\n");
}

static void test_enqueue_multiple(void)
{
    queue* q = queue_init();

    for (int i = 0; i < 100; ++i)
        queue_enqueue(q, i);

    ASSERT_EQ(100, q->vec->size);
    ASSERT_EQ(0, queue_front(q));

    queue_free(q);

    printf("[PASS] test_enqueue_multiple\n");
}

static void test_dequeue_single(void)
{
    queue* q = queue_init();

    queue_enqueue(q, 123);

    ASSERT_EQ(123, queue_dequeue(q));
    ASSERT_TRUE(queue_empty(q));

    queue_free(q);

    printf("[PASS] test_dequeue_single\n");
}

/*
 * Core queue invariant:
 * First In First Out
 */
static void test_fifo_property(void)
{
    queue* q = queue_init();

    for (int i = 0; i < 100; ++i)
        queue_enqueue(q, i);

    for (int i = 0; i < 100; ++i)
        ASSERT_EQ(i, queue_dequeue(q));

    ASSERT_TRUE(queue_empty(q));

    queue_free(q);

    printf("[PASS] test_fifo_property\n");
}

static void test_front(void)
{
    queue* q = queue_init();

    queue_enqueue(q, 10);
    queue_enqueue(q, 20);
    queue_enqueue(q, 30);

    ASSERT_EQ(10, queue_front(q));

    /* front should not remove the element */
    ASSERT_EQ(10, queue_front(q));
    ASSERT_EQ(0, q->head);

    queue_free(q);

    printf("[PASS] test_front\n");
}

static void test_empty_state(void)
{
    queue* q = queue_init();

    ASSERT_TRUE(queue_empty(q));

    queue_enqueue(q, 1);

    ASSERT_TRUE(!queue_empty(q));

    queue_dequeue(q);

    ASSERT_TRUE(queue_empty(q));

    queue_free(q);

    printf("[PASS] test_empty_state\n");
}

static void test_dequeue_empty(void)
{
    queue* q = queue_init();

    ASSERT_EQ(0, queue_dequeue(q));
    ASSERT_TRUE(queue_empty(q));

    queue_free(q);

    printf("[PASS] test_dequeue_empty\n");
}

static void test_front_empty(void)
{
    queue* q = queue_init();

    ASSERT_EQ(0, queue_front(q));

    queue_free(q);

    printf("[PASS] test_front_empty\n");
}

/*
 * Ensure head advances correctly
 * after repeated dequeues.
 */
static void test_head_progression(void)
{
    queue* q = queue_init();

    for (int i = 0; i < 10; ++i)
        queue_enqueue(q, i);

    for (int i = 0; i < 5; ++i)
        queue_dequeue(q);

    ASSERT_EQ(5, q->head);
    ASSERT_EQ(5, queue_front(q));

    queue_free(q);

    printf("[PASS] test_head_progression\n");
}

/*
 * Compact should reclaim consumed space
 * while preserving queue order.
 */
static void test_compact(void)
{
    queue* q = queue_init();

    for (int i = 0; i < 10; ++i)
        queue_enqueue(q, i);

    for (int i = 0; i < 5; ++i)
        ASSERT_EQ(i, queue_dequeue(q));

    queue_compact(q);

    ASSERT_EQ(0, q->head);
    ASSERT_EQ(5, q->vec->size);

    ASSERT_EQ(5, queue_front(q));

    for (int i = 5; i < 10; ++i)
        ASSERT_EQ(i, queue_dequeue(q));

    ASSERT_TRUE(queue_empty(q));

    queue_free(q);

    printf("[PASS] test_compact\n");
}

/*
 * Alternate enqueue/dequeue operations.
 * Useful for catching bookkeeping bugs.
 */
static void test_enqueue_dequeue_cycles(void)
{
    queue* q = queue_init();

    for (int i = 0; i < 10000; ++i)
    {
        queue_enqueue(q, i);

        ASSERT_EQ(i, queue_front(q));
        ASSERT_EQ(i, queue_dequeue(q));

        ASSERT_TRUE(queue_empty(q));
    }

    queue_free(q);

    printf("[PASS] test_enqueue_dequeue_cycles\n");
}

/*
 * Stress test growth and head movement.
 */
static void test_large_queue(void)
{
    queue* q = queue_init();

    const int N = 100000;

    for (int i = 0; i < N; ++i)
        queue_enqueue(q, i);

    ASSERT_EQ(0, queue_front(q));

    for (int i = 0; i < N; ++i)
        ASSERT_EQ(i, queue_dequeue(q));

    ASSERT_TRUE(queue_empty(q));

    queue_free(q);

    printf("[PASS] test_large_queue\n");
}

/*
 * Tests queue behavior after compaction
 * followed by more insertions.
 */
static void test_compact_then_enqueue(void)
{
    queue* q = queue_init();

    for (int i = 0; i < 20; ++i)
        queue_enqueue(q, i);

    for (int i = 0; i < 10; ++i)
        queue_dequeue(q);

    queue_compact(q);

    for (int i = 20; i < 30; ++i)
        queue_enqueue(q, i);

    for (int i = 10; i < 30; ++i)
        ASSERT_EQ(i, queue_dequeue(q));

    ASSERT_TRUE(queue_empty(q));

    queue_free(q);

    printf("[PASS] test_compact_then_enqueue\n");
}

int main(void)
{
    test_init();

    test_enqueue_single();
    test_enqueue_multiple();

    test_dequeue_single();

    test_fifo_property();

    test_front();

    test_empty_state();

    test_dequeue_empty();
    test_front_empty();

    test_head_progression();

    test_compact();

    test_enqueue_dequeue_cycles();

    test_compact_then_enqueue();

    test_large_queue();

    printf("\nALL TESTS PASSED\n");

    return 0;
}
```

