#include <stdio.h>
#include <stdlib.h>

#include "../src/stack.h"

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
    stack* s = stack_init();

    ASSERT_TRUE(s != NULL);
    ASSERT_TRUE(stack_empty(s));

    ASSERT_EQ(0, s->vec->size);

    stack_free(s);

    printf("[PASS] test_init\n");
}

static void test_push_single(void)
{
    stack* s = stack_init();

    stack_push(s, 42);

    ASSERT_EQ(42, stack_top(s));
    ASSERT_EQ(1, s->vec->size);

    stack_free(s);

    printf("[PASS] test_push_single\n");
}

static void test_push_multiple(void)
{
    stack* s = stack_init();

    for (int i = 0; i < 100; ++i)
        stack_push(s, i);

    ASSERT_EQ(99, stack_top(s));
    ASSERT_EQ(100, s->vec->size);

    stack_free(s);

    printf("[PASS] test_push_multiple\n");
}

static void test_pop_single(void)
{
    stack* s = stack_init();

    stack_push(s, 123);

    ASSERT_EQ(123, stack_pop(s));
    ASSERT_TRUE(stack_empty(s));

    stack_free(s);

    printf("[PASS] test_pop_single\n");
}

/*
 * Fundamental stack invariant:
 * last pushed == first popped
 */
static void test_lifo_property(void)
{
    stack* s = stack_init();

    for (int i = 0; i < 100; ++i)
        stack_push(s, i);

    for (int i = 99; i >= 0; --i)
        ASSERT_EQ(i, stack_pop(s));

    ASSERT_TRUE(stack_empty(s));

    stack_free(s);

    printf("[PASS] test_lifo_property\n");
}

static void test_top(void)
{
    stack* s = stack_init();

    stack_push(s, 10);
    stack_push(s, 20);
    stack_push(s, 30);

    ASSERT_EQ(30, stack_top(s));

    /* top shouldn't modify the stack */
    ASSERT_EQ(30, stack_top(s));
    ASSERT_EQ(3, s->vec->size);

    stack_free(s);

    printf("[PASS] test_top\n");
}

static void test_empty_state(void)
{
    stack* s = stack_init();

    ASSERT_TRUE(stack_empty(s));

    stack_push(s, 1);

    ASSERT_TRUE(!stack_empty(s));

    stack_pop(s);

    ASSERT_TRUE(stack_empty(s));

    stack_free(s);

    printf("[PASS] test_empty_state\n");
}

static void test_pop_empty(void)
{
    stack* s = stack_init();

    ASSERT_EQ(0, stack_pop(s));
    ASSERT_TRUE(stack_empty(s));

    stack_free(s);

    printf("[PASS] test_pop_empty\n");
}

static void test_top_empty(void)
{
    stack* s = stack_init();

    ASSERT_EQ(0, stack_top(s));

    stack_free(s);

    printf("[PASS] test_top_empty\n");
}

/*
 * Try to force multiple vector reallocations.
 * If growth logic is broken this usually finds it.
 */
static void test_large_stack(void)
{
    stack* s = stack_init();

    const int N = 100000;

    for (int i = 0; i < N; ++i)
        stack_push(s, i);

    ASSERT_EQ(N, s->vec->size);
    ASSERT_EQ(N - 1, stack_top(s));

    for (int i = N - 1; i >= 0; --i)
        ASSERT_EQ(i, stack_pop(s));

    ASSERT_TRUE(stack_empty(s));

    stack_free(s);

    printf("[PASS] test_large_stack\n");
}

/*
 * Alternate pushes and pops repeatedly.
 * Good for catching bookkeeping bugs.
 */
static void test_push_pop_cycles(void)
{
    stack* s = stack_init();

    for (int i = 0; i < 10000; ++i)
    {
        stack_push(s, i);

        ASSERT_EQ(i, stack_top(s));
        ASSERT_EQ(i, stack_pop(s));

        ASSERT_TRUE(stack_empty(s));
    }

    stack_free(s);

    printf("[PASS] test_push_pop_cycles\n");
}

void run_stack_tests(void)
{
    test_init();

    test_push_single();
    test_push_multiple();

    test_pop_single();

    test_top();

    test_empty_state();

    test_pop_empty();
    test_top_empty();

    test_lifo_property();

    test_push_pop_cycles();

    test_large_stack();

    printf("\nALL TESTS PASSED\n");

    return;
}
