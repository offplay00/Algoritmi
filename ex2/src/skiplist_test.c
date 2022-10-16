#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "unity.h"
#include "skiplist_utility.h"

struct _node {
  node** next;
  unsigned int size;
  void* item;
};

struct _skiplist {
  node *head;
  unsigned int max_level;
  int (*compare)(const void*, const void*);
};

static int int_compare(const void* x,const void* y) {
  int*a = (int*) x;
  int*b = (int*) y;
  return *a-*b;
}

static skiplist* try_list;

static int a = 4;
static int b = 170;
static int c = 4;
static int d = -3;

void setUp(void) {
  try_list = skiplist_new(int_compare);
}

void tearDown(void) {
  skiplist_free(try_list);
}

static void test_skiplist_is_empty_zero_el(void) {
  TEST_ASSERT_TRUE(try_list->head->next[1] == NULL);
}

static void test_skiplist_is_empty_one_el(void) {
  skiplist_insert(try_list,&a);
  TEST_ASSERT_FALSE(try_list->head->next[1] == NULL);
}

static void test_skiplist_is_ordered_four_elem(void) {
  skiplist_insert(try_list,&a);
  skiplist_insert(try_list,&b);
  skiplist_insert(try_list,&c);
  skiplist_insert(try_list,&d);
  TEST_ASSERT_TRUE(skiplist_is_ordered(try_list));
}

static void test_skiplist_searching_one_elem(void) {
  skiplist_insert(try_list,&a);
  skiplist_insert(try_list,&b);
  skiplist_insert(try_list,&c);
  skiplist_insert(try_list,&d);
  //skiplist_search return pointer of item found,cast it int and after compare with
  //real value of the item
  TEST_ASSERT_TRUE(*(int*) skiplist_search(try_list,&c) == c );
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_skiplist_is_empty_zero_el);
  RUN_TEST(test_skiplist_is_empty_one_el);
  RUN_TEST(test_skiplist_is_ordered_four_elem);
  RUN_TEST(test_skiplist_searching_one_elem);

  return UNITY_END();
}
