#include <stdio.h>
#include <string.h>
#include "sorted-list.h"

SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df) {

  SortedListPtr ls = malloc(sizeof(SortedListPtr));
  ls->list = NULL;
  ls->size = 0;
  ls->CompareT = cf;
  ls->DestructT = df;

  return ls;
}

void SLDestroy(SortedListPtr list) {

  free(list->list);
  free(list->CompareT);
  free(list->DestructT);
  free(list);

}

/*
 * Inserts a new item, referenced by *newObj, into the 
 * list in sorted order. Preforms this operation in O(n).
 */

int SLInsert(SortedListPtr list, void *newObj) {
  SortedListIteratorPtr slip = SLCreateIterator(list);
  
  if(newObj == NULL) {
    //SLDestroyIterator(slip);
    return 0;
  }


  //If the list is empty, we need to initalize the array
  //and add the new item
  if(list->size == 0) {
    list->list = malloc(sizeof(void*));
    list->list[0] = newObj;
    list->size = 1;
    //SLDestroyIterator(slip);
    return 1;
  }

  void *next = NULL;

  printf("Looping\n");
  while((next = SLNextItem(slip)) != NULL) {
    printf("Inner\n");
    if(list->CompareT(newObj, next) == -1) {
      continue;
      printf("Not at Fault\n");
    } else {
      printf("Nope!\n");
      insertAt(list, slip, newObj);
      return 1;
    }
  }


  

  //SLDestroyIterator(slip);
  return 0;
}

void insertAt(SortedListPtr list, SortedListIteratorPtr iter, void *newObj) {
  //Insertion happens in 3 parts
  //
  // Malloc a buffer that is the size of the current array, plus one
  //Copy the prefix portion of the buffer, add in newObj, copy
  //the suffix poriton of the buffer.
  int i, j;
  void **buffer = malloc(list->size + 1);
  list->size += 1;
  //Special Case, curr_index = 0
  


  for(i = 0; i < iter->curr_index; i++) {
    buffer[i] = list->list[i];
  }
  buffer[i] = newObj;
  for(j = iter->curr_index + 1; j < list->size + 1; j++) {
    buffer[j] = list->list[j - 1];
  }


  //Free the current list
  //free(list->list);
  list->list = buffer;
}


int SLRemove(SortedListPtr list, void *newObj) {

  return 0;
}

/* Creates a SortedListIterator for the given SortedListPtr
 * Usage: 
 * SLDestroyIterator(iter): Frees the memory allocated for the iterator
 * SLGetItem(iter): Gets the current item the iterator is focused on
 *                  without advancing to the next item in the list.
 * SLNextItem(iter): Gets the next item in the SortedListPtr
 *                   
 */


SortedListIteratorPtr SLCreateIterator(SortedListPtr list) {
  
  SortedListIteratorPtr slip = malloc(sizeof(SortedListIteratorPtr));
  
  slip->listPtr = list;
  
  void *first;
  if(list->size == 0) {
    first = NULL;
  } else {
    first = list->list[0];
  }

  slip->first = first;

  slip->next = NULL;
  slip->curr_index = -1;



  return slip;
}

void* SLGetItem(SortedListIteratorPtr iter) {
  return iter->next;
}

void* SLNextItem(SortedListIteratorPtr iter) {
  int curr_index = iter->curr_index;
  int list_size = iter->listPtr->size;

  if(curr_index + 1 > list_size) {
    iter->next = NULL;
    return NULL;
  }

  void *next = iter->listPtr->list[curr_index + 1];
  iter->curr_index += 1;
  iter->next = next;

  return iter->next;
}

void SLDestroyIterator(SortedListIteratorPtr iter) {
  //TODO Free other stuffs
  free(iter);

}

//Debug Testing

int compareInts(void *p1, void *p2)
{
  int i1 = *(int*)p1;
  int i2 = *(int*)p2;

  return i1 - i2;
}

int compareDoubles(void *p1, void *p2)
{
  double d1 = *(double*)p1;
  double d2 = *(double*)p2;

  return (d1 < d2) ? -1 : ((d1 > d2) ? 1 : 0);
}

int compareStrings(void *p1, void *p2)
{
  char *s1 = p1;
  char *s2 = p2;

  return strcmp(s1, s2);
}

//Destructor functions
void destroyBasicTypeAlloc(void *p){
  //For pointers to basic data types (int*,char*,double*,...)
  //Use for allocated memory (malloc,calloc,etc.)
  free(p);
}

void destroyBasicTypeNoAlloc(void *p) {
  //For pointers to basic data types (int*,char*,double*,...)
  //Use for memory that has not been allocated (e.g., "int x = 5;SLInsert(mylist,&x);SLRemove(mylist,&x);")
  return;
}


int main()
{
  int x = 0;
  int y = 1;
  int z = 2;



  printf("Hello World");
  SortedListPtr ls = SLCreate(&compareInts, &destroyBasicTypeNoAlloc);
  SLInsert(ls, &x);
  SLInsert(ls, &y);
  SLInsert(ls, &z);


}
