#include "records_utility.h"
#include "sorting_utility.h"

#define MAX 20000000

clock_t start,end;
double benchmark;

void sorting(void (*sort)(void**,int,int,int(*comp)(const void*,const void*))) {
  Records** a;
  benchmark = 0.0;
  a = Records_memory_alloc(MAX);
  csv_reader(a,"../src/records.csv",MAX);
  int (*comp)(const void*,const void*) = Records_field1_comp;
  start = clock();
  (*sort)((void**)a,0,MAX-1,comp);
  end = clock();
  Records_free(a,MAX);
  benchmark += (double)(end-start)/CLOCKS_PER_SEC;
  a = Records_memory_alloc(MAX);
  csv_reader(a,"../src/records.csv",MAX);
  comp = Records_field2_comp;
  start = clock();
  (*sort)((void**)a,0,MAX-1,comp);
  end = clock();
  Records_free(a,MAX);
  benchmark += (double)(end-start)/CLOCKS_PER_SEC;
  a = Records_memory_alloc(MAX);
  csv_reader(a,"../src/records.csv",MAX);
  comp = Records_field3_comp;
  start = clock();
  (*sort)((void**)a,0,MAX-1,comp);
  end = clock();
  Records_free(a,MAX);
  benchmark += (double)(end-start)/CLOCKS_PER_SEC;
  printf("Total time spent sorting is: %f\n",benchmark);
}

//the program ask the user to input a number to launch specific sorting method.
int main() {
  void (*sort)(void**,int,int,int(*comp)(const void*,const void*));
  int select = 0;
  printf("%s","Select a sorting method:\n1)quicksort\n2)random_quicksort\n3)insertion_sort\n");
  scanf("%d",&select);
  switch (select)
  {
  case 1:
    sort = quicksort;
    sorting(sort);
    printf("quicksort is completed!");
    break;
  case 2:
    sort = random_quicksort;
    sorting(sort);
    printf("random quicksort is completed!");
    break;
  case 3:
    sort = insertion_sort;
    sorting(sort);
    printf("insertion sort is completed!");
    break;

  default:
    printf("BAD Input!");
    break;
  }
  return 0;
}
