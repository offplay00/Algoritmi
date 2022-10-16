#include "records_utility.h"
#include "sorting_utility.h"

#define MAX 200

int compare(const void* x,const void* y) {
    int *a,*b;
    a = (int*) x;
    b = (int*) y;
    if(*a-*b > 0)
        return 1;
    else if(*a-*b < 0)
        return -1;
    else 
        return 0;
}

int main() {
    srand((unsigned) time(NULL));
    int**x;
    int (*comp)(const void*,const void*) = compare;
    x = (int**) malloc(MAX*sizeof(int*));
    for(int i = 0;i < MAX;i++) {
        x[i] = (int*) malloc(sizeof(int));
        *x[i] = rand();
    }
    printf("%d",is_sorted((void**)x,MAX-1,compare));
    insertion_sort((void**) x,0,MAX-1,comp);
    printf("%d",is_sorted((void**)x,MAX-1,compare));
}
