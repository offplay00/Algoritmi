#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>
#include "skiplist_utility.h"

#define MAX_WORD_TEST 100
#define BUF_SIZE 1064

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

int str_compare(const void* x,const void* y) {
  char* a = (char*) x;
  char* b = (char*) y;
  return strcmp(a,b);
}

//this function was taken from stackoverflow
static void remove_punct_and_make_lower_case(char *p) {
  char *src = p, *dst = p;
  while (*src) {
    if (ispunct((unsigned char)*src)) {
      src++; // Skip this character
    }
    else if (isupper((unsigned char)*src)) {
      *dst++ = (char) tolower((unsigned char)*src); //  Make it lowercase
      src++;
    }
    else if (src == dst) {
      src++; // Increment both pointers without copying
      dst++;
    }
    else {
      *dst++ = *src++; //Copy character
    }
  }
  *dst = 0;
}

//take in input the file and put all element in a skiplist
static void reader(skiplist* list,const char* path) {
  FILE* fp ;
  char buf[BUF_SIZE];
  printf("Open File...\n");
  if((fp = fopen(path,"r") ) == NULL) {
    printf("Can't open file!");
    exit(EXIT_FAILURE);
  }
  while((fscanf(fp,"%s",buf)) == 1) {
     skiplist_insert(list,strdup(buf));
  }
  fclose(fp);
  printf("All file read!\n");
}

//take in input the fail has to be correct and write in order the word that aren't
//correct for the dictionary (skipilist)
static void correction(skiplist* list,const char* path) {
  FILE* fp;
  char *buf;
  buf = malloc(20*sizeof(char));
  printf("Open File...\n");
  if((fp = fopen(path,"r") ) == NULL) {
    printf("Can't open file!");
    exit(EXIT_FAILURE);
  }
  while((fscanf(fp,"%s",buf)) == 1) {
    //the skiplist contain only word lowercase and without punctation
    remove_punct_and_make_lower_case(buf);
    if(!skiplist_search(list,buf))
      printf("%s\n",buf);
  }
  fclose(fp);
  printf("correction end!\n");
}

int main(int argc, char const *argv[]) {
  if(argc == 3) {
    skiplist* list = skiplist_new(str_compare);
    srand((unsigned int)time(NULL));
    const char* path = argv[argc-2];
    reader(list,path);
    path = argv[argc-1];
    correction(list,path);
    skiplist_free(list);
    return 0;
  }else {
    printf("main: main function must have 2 string of path when execute!");
    exit(EXIT_FAILURE);
  }
}
