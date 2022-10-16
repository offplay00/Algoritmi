#include "records_utility.h"

int Records_id_get(Records* a) {return a->id;}

void Records_id_set(Records* a,int x) {a->id = x;}

char* Records_field1_get(Records* a) {return a->field1;}

void Records_field1_set(Records* a,char* x) {a->field1 = x;}

int Records_field2_get(Records* a) {return a->field2;}

void Records_field2_set(Records* a,int x) {a->field2 = x;}

float Records_field3_get(Records* a) {return a->field3;}

void Records_field3_set(Records* a,float x) {a->field3 = x;}

Records** Records_memory_alloc(int size) {
  Records** a;
  a = (Records**) malloc(size*sizeof(Records*));
  for(int i  = 0;i < size;i++) {
    a[i] = (Records*) malloc(sizeof(Records));
    Records_field1_set(a[i],"");
    Records_field2_set(a[i],0);
    Records_field3_set(a[i],0.0);
  }
  return a;
}

void Records_free(Records** a,int size) {
  for(int i = 0;i<size;i++)
    free(a[i]);
  free(a);
  a = NULL;
}

int Records_empty(Records** a,int size) {
  if(a == NULL) {
    fprintf(stderr,"Records_empty: Records parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  for(int i = 0;i < size;i++)
    if(!(strlen(Records_field1_get(a[0])) == 0) && !(Records_field2_get(a[0])) == 0 && !(Records_field3_get(a[0]) == 0.0))
      return 0;
  return 1;
}

void csv_reader(Records** a,char* path,int length) {
  FILE* fp;
  char buf[BUF_SIZE],*token;
  if((fp = fopen(path,"r")) == NULL) {
    printf("CSV_READER: Error open file path!");
    exit(EXIT_FAILURE);
  }
  printf("Open file...\n");
  for(int i = 0;i<length;i++) {
    fgets(buf,100,fp);
    token = strtok(buf,",");
    Records_id_set(a[i],atoi(token));
    token = strtok(NULL,",");
    Records_field1_set(a[i],strdup(token));
    token = strtok(NULL,",");
    Records_field2_set(a[i],atoi(token));
    token = strtok(NULL,",");
    Records_field3_set(a[i],strtof(token,NULL));
  }
  fclose(fp);
  printf("read done!\n");
}

int Records_field1_comp(const void* a,const void* b) {
  Records* v1,*v2;
  v1 = (Records*) a;
  v2 = (Records*) b;
  return strcmp(Records_field1_get(v1),Records_field1_get(v2));
}

int Records_field2_comp(const void* a,const void* b) {
  Records* v1,*v2;
  v1 = (Records*) a;
  v2 = (Records*) b;
  return Records_field2_get(v1)-Records_field2_get(v2);
}

int Records_field3_comp(const void* a,const void* b) {
  Records* v1,*v2;
  v1 = (Records*) a;
  v2 = (Records*) b;
  if(Records_field3_get(v1)-Records_field3_get(v2) > 0)
    return 1;
  else if(Records_field3_get(v1)-Records_field3_get(v2) < 0)
    return -1;
  else 
    return 0;
}
