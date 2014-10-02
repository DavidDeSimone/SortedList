#include <stdio.h>
#include "sorted-list.h"

SortedListPtr SLCreate(CompareFunT cf, DestructFunT df) {

  SortedListPtr ls = malloc(sizeof(SortedListPtr));
  ls->list = NULL;
  ls->size = 0;
  ls->CompareT = &cf;
  ls->DestructT = &df;



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
    SLDestroyIterator(slip);
    return 0;
  }


  //If the list is empty, we need to initalize the array
  //and add the new item
  if(list->size == 0) {
    list->list = malloc(sizeof(void*));
    list->list[0] = newObj;
    list->size = 1;
    SLDestroyIterator(slip);
    return 1;
  }

  void *next = NULL;
  while((next = SLNextItem) != NULL) {
    if(list->CompareT(newObj, next) == 1) {
      insertAt(list, slip, newObj);
      SLDestroyIterator(slip);
      return 1;
    }
  }


  

  SLDestroyIterator(slip);
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


  for(i = 0; i < iter->curr_index; i++) {
    buffer[i] = iter->list[i];
  }
  buffer[i] = newObj;
  for(j = iter->curr_index + 1; j < list->size + 1; j++) {
    buffer[j] = iter->list[j - 1];
  }


  //Free the current list
  free(list->list);
  list->buffer;
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
  slip->curr_index = 0;



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

  void *next = iter->listPtr->list[curr_index];
  iter->curr_index += 1;
  iter->next = next;

  return iter->next;
}
