// test_linked_list.c

#include <stdio.h>
#include <stdlib.h>

#include "../src/linked_list.h"

#define ASSERT_TRUE(expr)                                                      \
  do {                                                                         \
    if (!(expr)) {                                                             \
      printf("[FAIL] %s:%d -> %s\n", __FILE__, __LINE__, #expr);               \
      exit(1);                                                                 \
    }                                                                          \
  } while (0)

#define ASSERT_EQ_INT(expected, actual)                                        \
  do {                                                                         \
    if ((expected) != (actual)) {                                              \
      printf("[FAIL] %s:%d\n", __FILE__, __LINE__);                            \
      printf("Expected %d, got %d\n", (expected), (actual));                   \
      exit(1);                                                                 \
    }                                                                          \
  } while (0)

static int list_length(Node *head) {
  int count = 0;

  while (head) {
    count++;
    head = head->next;
  }

  return count;
}

static void test_init_list() {
  int arr[] = {1, 2, 3, 4, 5};

  Node *head = initList(arr, 5);

  ASSERT_EQ_INT(5, list_length(head));

  ASSERT_EQ_INT(1, head->value);
  ASSERT_EQ_INT(2, head->next->value);
  ASSERT_EQ_INT(3, head->next->next->value);

  destroyList(&head);

  ASSERT_TRUE(head == NULL);

  printf("[PASS] test_init_list\n");
}

static void test_insert_beginning() {
  int arr[] = {2, 3, 4};

  Node *head = initList(arr, 3);

  InsertAtBeginning(&head, 1);

  ASSERT_EQ_INT(1, head->value);
  ASSERT_EQ_INT(4, list_length(head));

  destroyList(&head);

  printf("[PASS] test_insert_beginning\n");
}

static void test_insert_end() {
  int arr[] = {1, 2, 3};

  Node *head = initList(arr, 3);

  InsertAtEnd(&head, 4);

  Node *iter = head;

  while (iter->next)
    iter = iter->next;

  ASSERT_EQ_INT(4, iter->value);
  ASSERT_EQ_INT(4, list_length(head));

  destroyList(&head);

  printf("[PASS] test_insert_end\n");
}

static void test_delete_beginning() {
  int arr[] = {1, 2, 3, 4};

  Node *head = initList(arr, 4);

  DeleteAtBeginning(&head);

  ASSERT_EQ_INT(2, head->value);
  ASSERT_EQ_INT(3, list_length(head));

  destroyList(&head);

  printf("[PASS] test_delete_beginning\n");
}

static void test_delete_end() {
  int arr[] = {1, 2, 3, 4};

  Node *head = initList(arr, 4);

  DeleteAtEnd(&head);

  Node *iter = head;

  while (iter->next)
    iter = iter->next;

  ASSERT_EQ_INT(3, iter->value);
  ASSERT_EQ_INT(3, list_length(head));

  destroyList(&head);

  printf("[PASS] test_delete_end\n");
}

static void test_destroy() {
  int arr[] = {1, 2, 3};

  Node *head = initList(arr, 3);

  destroyList(&head);

  ASSERT_TRUE(head == NULL);

  printf("[PASS] test_destroy\n");
}

int main(void) {
  test_init_list();
  test_insert_beginning();
  test_insert_end();
  test_delete_beginning();
  test_delete_end();
  test_destroy();

  printf("\nALL TESTS PASSED\n");

  return 0;
}
