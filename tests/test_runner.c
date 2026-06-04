#include <stdio.h>

// implemented in each test file
void run_vector_tests(void);
void run_stack_tests(void);
void run_queue_tests(void);
void run_linked_list_tests(void);

int main(void)
{
    printf("\nVector Tests:");
    run_vector_tests();

    printf("\nStack Tests:");
    run_stack_tests();

    printf("\nQueue Tests:");
    run_queue_tests();

    printf("\nLinked List Tests:");
    run_linked_list_tests();

    printf("ALL TESTS PASSED\n");
    return 0;
}

