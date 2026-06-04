#include <stdio.h>
#include <stdlib.h>

#include "../src/vector.h"

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

static void test_init_empty(void)
{
    vector* v = vec_init(NULL, 0);

    ASSERT_EQ(0, v->size);
    ASSERT_EQ(0, v->capacity);
    ASSERT_TRUE(v->data == NULL);

    vec_free(v);

    printf("[PASS] test_init_empty\n");
}

static void test_init_array(void)
{
    int arr[] = {1, 2, 3, 4, 5};

    vector* v = vec_init(arr, 5);

    ASSERT_EQ(5, v->size);

    for (int i = 0; i < 5; ++i)
        ASSERT_EQ(arr[i], v->data[i]);

    vec_free(v);

    printf("[PASS] test_init_array\n");
}

static void test_push(void)
{
    vector* v = vec_init(NULL, 0);

    vec_push(v, 10);

    ASSERT_EQ(1, v->size);
    ASSERT_EQ(10, v->data[0]);

    vec_free(v);

    printf("[PASS] test_push\n");
}

static void test_multiple_push(void)
{
    vector* v = vec_init(NULL, 0);

    for (int i = 0; i < 100; ++i)
        vec_push(v, i);

    ASSERT_EQ(100, v->size);

    for (int i = 0; i < 100; ++i)
        ASSERT_EQ(i, v->data[i]);

    vec_free(v);

    printf("[PASS] test_multiple_push\n");
}

static void test_capacity_growth(void)
{
    vector* v = vec_init(NULL, 0);

    size_t previous_capacity = v->capacity;

    for (int i = 0; i < 100; ++i)
    {
        vec_push(v, i);

        ASSERT_TRUE(v->capacity >= v->size);

        if (v->capacity != previous_capacity)
        {
            ASSERT_TRUE(v->capacity > previous_capacity);
            previous_capacity = v->capacity;
        }
    }

    vec_free(v);

    printf("[PASS] test_capacity_growth\n");
}

static void test_pop(void)
{
    int arr[] = {1, 2, 3};

    vector* v = vec_init(arr, 3);

    int popped = vec_pop(v);

    ASSERT_EQ(3, popped);
    ASSERT_EQ(2, v->size);

    vec_free(v);

    printf("[PASS] test_pop\n");
}

/*
 * Vector should behave like a stack when
 * elements are removed from the end.
 */
static void test_lifo_property(void)
{
    vector* v = vec_init(NULL, 0);

    for (int i = 0; i < 100; ++i)
        vec_push(v, i);

    for (int i = 99; i >= 0; --i)
        ASSERT_EQ(i, vec_pop(v));

    ASSERT_EQ(0, v->size);

    vec_free(v);

    printf("[PASS] test_lifo_property\n");
}

static void test_replace(void)
{
    int arr[] = {1, 2, 3};

    vector* v = vec_init(arr, 3);

    vec_replace(v, 1, 42);

    ASSERT_EQ(42, v->data[1]);
    ASSERT_EQ(3, v->size);

    vec_free(v);

    printf("[PASS] test_replace\n");
}

static void test_reserve(void)
{
    vector* v = vec_init(NULL, 0);

    reserve(v, 128);

    ASSERT_EQ(128, v->capacity);
    ASSERT_EQ(0, v->size);

    vec_free(v);

    printf("[PASS] test_reserve\n");
}

/*
 * This is intentionally a bug-finding test.
 *
 * Reserve should not destroy existing contents.
 * Current implementation resets size and loses data.
 *
 * If this test fails, the implementation needs fixing,
 * not the test.
 */
static void test_reserve_preserves_data(void)
{
    vector* v = vec_init(NULL, 0);

    vec_push(v, 10);
    vec_push(v, 20);

    reserve(v, 100);

    ASSERT_EQ(2, v->size);
    ASSERT_EQ(10, v->data[0]);
    ASSERT_EQ(20, v->data[1]);

    vec_free(v);

    printf("[PASS] test_reserve_preserves_data\n");
}

/*
 * Stress growth logic and allocator usage.
 * If growth logic is wrong this tends to explode.
 */
static void test_large_push(void)
{
    vector* v = vec_init(NULL, 0);

    const int N = 1000000;

    for (int i = 0; i < N; ++i)
        vec_push(v, i);

    ASSERT_EQ(N, v->size);
    ASSERT_EQ(N - 1, v->data[N - 1]);

    vec_free(v);

    printf("[PASS] test_large_push\n");
}

static void test_pop_empty(void)
{
    vector* v = vec_init(NULL, 0);

    ASSERT_EQ(0, vec_pop(v));
    ASSERT_EQ(0, v->size);

    vec_free(v);

    printf("[PASS] test_pop_empty\n");
}

void run_vector_tests(void)
{
    test_init_empty();
    test_init_array();

    test_push();
    test_multiple_push();

    test_capacity_growth();

    test_pop();
    test_pop_empty();

    test_lifo_property();

    test_replace();

    test_reserve();
    test_reserve_preserves_data();

    test_large_push();

    printf("\nALL TESTS PASSED\n");

    return;
}
