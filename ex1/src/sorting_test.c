#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "unity.h"
#include "records_utility.h"
#include "sorting_utility.h"
/*
Test for Records and sorting.
*/

//definition for number of element in the array
#define NORMAL 100

static Records** try_rec;
static void (*q_sort)(void**,int,int,int(*comp)(const void*,const void*));
static void (*rand_q_sort)(void**,int,int,int(*comp)(const void*,const void*));
static void (*insert)(void**,int,int,int(*comp)(const void*,const void*));
static int (*comp1)(const void*,const void*);
static int (*comp2)(const void*,const void*);
static int (*comp3)(const void*,const void*);

void setUp(void){
  try_rec = Records_memory_alloc(3);
  q_sort = quicksort;
  rand_q_sort = random_quicksort;
  insert = insertion_sort;
  comp1 = Records_field1_comp;
  comp2 = Records_field2_comp;
  comp3 = Records_field3_comp;
}

void tearDown(void){
  Records_free(try_rec,3);
  q_sort = NULL;
  rand_q_sort = NULL;
  insert = NULL;
  comp1 = NULL;
  comp2 = NULL;
  comp3 = NULL;
}

static void test_Records_is_empty_zero_el(void){
  TEST_ASSERT_TRUE(Records_empty(try_rec,3) == 1);
}

static void test_Records_is_empty_one_el(void){
 Records_field1_set(try_rec[0],"elem");
 TEST_ASSERT_FALSE(Records_empty(try_rec,3) == 0);
}

static void test_Records_is_empty_three_el(void){
 Records_field1_set(try_rec[0],"elem1");
 Records_field1_set(try_rec[1],"elem2");
 Records_field1_set(try_rec[2],"elem3");
 TEST_ASSERT_FALSE(Records_empty(try_rec,3) == 0);
}

static void test_quicksort_zero_elem(void) {
  q_sort((void**)try_rec,0,2,comp1);
  TEST_ASSERT_TRUE(is_sorted((void**)try_rec,2,comp1) == 1);
}

static void test_quicksort_equal_elem(void) {
  Records** exp_rec = Records_memory_alloc(NORMAL);
  for(int i = 0;i < NORMAL;i++)
    Records_field2_set(exp_rec[i],0);
  q_sort((void**)exp_rec,0,NORMAL-1,comp2);
  TEST_ASSERT_TRUE(is_sorted((void**)exp_rec,NORMAL,comp2) == 1);
  Records_free(exp_rec,NORMAL);
}

static void test_quicksort_multiple_elem(void) {
  Records** exp_rec = Records_memory_alloc(NORMAL);
  for(int i = 0;i < NORMAL;i++)
    Records_field2_set(exp_rec[i],(int) rand()%NORMAL);
  q_sort((void**)exp_rec,0,NORMAL-1,comp2);
  TEST_ASSERT_TRUE(is_sorted((void**)exp_rec,NORMAL,comp2) == 1);
  Records_free(exp_rec,NORMAL);
}

static void test_random_quicksort_zero_elem(void) {
  rand_q_sort((void**)try_rec,0,2,comp1);
  TEST_ASSERT_TRUE(is_sorted((void**)try_rec,2,comp1) == 1);
}

static void test_random_quicksort_equal_elem(void) {
  Records** exp_rec = Records_memory_alloc(NORMAL);
  for(int i = 0;i < NORMAL;i++)
    Records_field2_set(exp_rec[i],0);
  rand_q_sort((void**)exp_rec,0,NORMAL-1,comp2);
  TEST_ASSERT_TRUE(is_sorted((void**)exp_rec,NORMAL,comp2) == 1);
  Records_free(exp_rec,NORMAL);
}

static void test_random_quicksort_multiple_elem(void) {
  Records** exp_rec = Records_memory_alloc(NORMAL);
  for(int i = 0;i < NORMAL;i++)
    Records_field2_set(exp_rec[i],(int) rand()%NORMAL);
  rand_q_sort((void**)exp_rec,0,NORMAL-1,comp2);
  TEST_ASSERT_TRUE(is_sorted((void**)exp_rec,NORMAL,comp2) == 1);
  Records_free(exp_rec,NORMAL);
}

static void test_insert_zero_elem() {
  insert((void**)try_rec,0,2,comp1);
  TEST_ASSERT_TRUE(is_sorted((void**)try_rec,2,comp1) == 1);
}

static void test_insert_equal_elem(void) {
  Records** exp_rec = Records_memory_alloc(NORMAL);
  for(int i = 0;i < NORMAL;i++)
    Records_field2_set(exp_rec[i],0);
  insert((void**)exp_rec,0,NORMAL-1,comp2);
  TEST_ASSERT_TRUE(is_sorted((void**)exp_rec,NORMAL,comp2) == 1);
  Records_free(exp_rec,NORMAL);
}

static void test_insert_multiple_elem(void) {
  Records** exp_rec = Records_memory_alloc(NORMAL);
  for(int i = 0;i < NORMAL;i++)
    Records_field2_set(exp_rec[i],(int) rand());
  insert((void**)exp_rec,0,NORMAL-1,comp2);
  TEST_ASSERT_TRUE(is_sorted((void**)exp_rec,NORMAL-1,comp2) == 1);
  Records_free(exp_rec,NORMAL);
}


int main(void) {

  //test session
  UNITY_BEGIN();
  //RECORDS
  RUN_TEST(test_Records_is_empty_zero_el);
  RUN_TEST(test_Records_is_empty_one_el);
  RUN_TEST(test_Records_is_empty_three_el);
  //QUICKSORT
  RUN_TEST(test_quicksort_zero_elem);
  RUN_TEST(test_quicksort_equal_elem);
  RUN_TEST(test_quicksort_multiple_elem);
  //RANDOM PIVOT QUICKSORT
  RUN_TEST(test_random_quicksort_zero_elem);
  RUN_TEST(test_random_quicksort_equal_elem);
  RUN_TEST(test_random_quicksort_multiple_elem);
  //BINARY_INSERTION_SORT
  RUN_TEST(test_insert_zero_elem);
  RUN_TEST(test_insert_equal_elem);
  RUN_TEST(test_insert_multiple_elem);

  return UNITY_END();
}
