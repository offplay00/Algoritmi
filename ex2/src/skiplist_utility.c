#include <stdlib.h>
#include <stdio.h>
#include <time.h>
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

static double random() { return (double)rand() / (double)((unsigned)RAND_MAX + 1); }

static unsigned int random_level() {
  unsigned int lvl = 1;
  while(random() < 0.5 && lvl < MAX_HEIGHT)
    lvl++;
  return lvl;
}

skiplist* skiplist_new(int (*comp)(const void*, const void*)) {
  skiplist* list = (skiplist*) malloc(sizeof(skiplist)); //first malloc
  list->compare = comp;
  list->max_level = (MAX_HEIGHT + 1); //+1 because 0 dosen't count in the skiplist struct
  node* x = (node*) malloc(sizeof(node)); //second malloc
  list->head = x;
  x->size = (MAX_HEIGHT + 1); //same as max_level
  x->next = (node**) malloc(x->size*sizeof(node*)); //n-size malloc
  for(unsigned int i = 0;i < x->size;i++) {
    x->next[i] = NULL; //NULL because skiplist is empty
  }
  return list;
}

void skiplist_free(skiplist* list) {
  for(unsigned int i = 0;i < list->max_level;i++)
    free(list->head->next[i]); //n-size free
  free(list->head); //second free
  free(list); //third free
}

void skiplist_insert(skiplist* list,void* l) {
  node* new = (node*) malloc(sizeof(node));
  new->size = (random_level() + 1); // size need to be > 1
  new->item = l;
  new->next = (node**) malloc(new->size*sizeof(node*));
  for(unsigned int i = 0;i < new->size;i++)
    new->next[i] = NULL;
  //because the size of maximum node is changed from MAX_HEIGHT skiplist need
  //to point all of new->next nodes. this part of the function realloc the memory
  //for contain all necessary next pointer.
  if(new->size > list->max_level) {
    skiplist* tmp = malloc(sizeof(skiplist));
    tmp->head = list->head;
    list->max_level = new->size;
    tmp->head->next = realloc(list->head->next,list->max_level*sizeof(node*));
    if(tmp == NULL) {
      printf("Error!");
      exit(EXIT_FAILURE);
    } else
      list = tmp;
  }
  node* x = list->head;
  for(unsigned int k = list->max_level-1;k >= 1; k--) {
    if((void*) x->next[k] == NULL || list->compare(new->item,x->next[k]->item) < 0) {
      if(k < new->size) {
        new->next[k] = x->next[k]; //put the item between x->head and x->next
        x->next[k] = new;
      }
    }
    else {
      x = x->next[k];
      k++;
    }
  }
}

void* skiplist_search(skiplist* list,void* l) {
  node* x = list->head;
  for(unsigned int i = list->max_level - 1;i >= 1;i--) {
    while(x->next[i] && list->compare(x->next[i]->item,l) < 0)
      x = x->next[i];
  }
  x = x->next[1];
  if(list->compare(x->item,l) == 0) {
    return x->item;
  }
  return NULL;
}

int skiplist_is_ordered(skiplist* list) {
  node* x = list->head;
  for(;x->next[1]->next[1] != NULL;x = x->next[1]) {
    if(list->compare(x->next[1]->item,x->next[1]->next[1]->item) > 0)
      return 0;
  }
  return 1;
}
