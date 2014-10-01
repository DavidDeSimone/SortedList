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

int SLInsert(SortedListPtr list, void *newObj) {

  return 0;
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
