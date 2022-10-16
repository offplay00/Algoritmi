#ifndef skiplist_UTILITY_H_AHJSDKHSBCJKHSAJIWOP
#define skiplist_UTILITY_H_AHJSDKHSBCJKHSAJIWOP

//MAX_HEIGHT define the max number of next pointer could have a single node
#define MAX_HEIGHT 20

typedef struct _node node;

typedef struct _skiplist skiplist;

/*
  create an empty skiplist with MAX_HEIGHT number of next and compare method
  for comparing elements in skiplist (because of generic item),this function
  alloc memory for 1 skiplist, 1 head node and MAX_HEIGHT+1 next node pointer
  all next node pointer are pointing NULL this because skiplist is empty
*/
skiplist* skiplist_new(int (*comp)(const void*,const void*));

/*
  insert an element in the skiplist, this particoular function doesn't control
  what type of item could be inserted, for this reason skiplist could have multiple
  type of item and this could cause a bug when trying to fit the item in correct
  position of skiplist. For fix this problem this function must have another input
  like size_t. Insert an elemnt in skiplist has O(log n) complexity.
*/
void skiplist_insert(skiplist*,void*);
/*
  search an element in skiplist, this function return the element itself if it is
  in the skiplist, NULL otherwise. This algorithm has O(log n) complexity thanks of
  probabilistic method of searching.
*/
void* skiplist_search(skiplist*,void*);
/*
  free all the memory created for a skiplist
*/
void skiplist_free(skiplist*);
/*
  binary algorithm with O(n) complexity, take a skiplist in input and
  return 1 if the skiplist is ordered 0 otherwise.
*/
int skiplist_is_ordered(skiplist* list);

#endif
