#include "sorting_utility.h"

int is_sorted(void** arr,int end,int(*comp)(const void*,const void*)) {
  for(int i = 0;i < end - 1;i++)
    if(comp(arr[i],arr[i+1]) > 0)
      return 0;
  return 1;
}

static void swap(void** arr,int i,int j) {
  void* tmp;
  tmp = arr[i];
  arr[i] = arr[j];
  arr[j] = tmp;
}

static int random_pivot(int end) { return rand()%end;}

//That function is not used but allow to use the middle element of the array as a pivot
static int middle_pivot(int beg,int end) {return (beg + end)/2; }

static void partition(void** arr,int beg,int end,int* l,int* r,int(*comp)(const void*,const void*)) {
  void* pivot = arr[end];
  *l = beg; *r = beg;
  int u = end;
  while(*r <= u) {
    if(comp(arr[(*r)], pivot) < 0) {
      swap(arr,*l,*r);
      (*l)++; (*r)++;
    } else if(comp(arr[(*r)], pivot) > 0) {
      swap(arr, *r, u);
      u--;
    } else (*r)++;
  }
}

void quicksort(void** arr,int beg, int end,int(*comp)(const void*,const void*)) {
    if (beg < end) {
      int l,r;
      partition(arr,beg,end,&l,&r,comp);
      quicksort(arr,beg,l-1,comp);
      quicksort(arr,r,end,comp);
    }
}

static void random_partition(void** arr,int beg,int end,int* l,int* r,int(*comp)(const void*,const void*)) {
  swap(arr,end,random_pivot(end));
  void *pivot = arr[end];
  *l = beg; *r = beg;
  int u = end;
  while(*r <= u) {
    if(comp(arr[*r], pivot) < 0) {
      swap(arr,*l,*r);
      (*l)++; (*r)++;
    } else if(comp(arr[*r], pivot) > 0) {
      swap(arr, *r, u);
      u--;
    } else (*r)++;
  }
}

void random_quicksort(void** arr,int beg, int end,int(*comp)(const void*,const void*)) {
    if (beg < end) {
      int l,r;
      random_partition(arr,beg,end,&l,&r,comp);
      quicksort(arr,beg,l-1,comp);
      quicksort(arr,r,end,comp);
    }
}

static int binary_search(void** arr, void* item, int end, int(*comp)(const void*,const void*)) {
  int b = 0, e = end,mid;
  while(b <= e) {
    mid = (b + e) / 2;
    if(comp(arr[mid],item) == 0)
      return mid;
    else if(comp(arr[mid],item) < 0)
      b = mid + 1;
    else
      e = mid - 1;
  }
  return b;
}

void insertion_sort(void** arr,int beg,int end,int(*comp)(const void*,const void*)) {
  int j;
  void* item;
  for(int i = beg + 1; i < end; i++) {
    item = arr[i];
    j = binary_search(arr,item,i - 1,comp);
    for(int k = i - 1;k >= j; k--) {
      arr[k+1] = arr[k];
    }
    arr[j] = item;
  }
}
