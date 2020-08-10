//NMEC: ...
//NOME: ...
//
// João Manuel Rodrigues, AlgC, May 2020
//
// A SchedulingSequence based on a SORTED LIST.

//// PROCURE ... E COMPLETE ////

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "SchedulingSequence.h"

// You may add auxiliary definitions and declarations here, if you need to.

// Comparison function to be used in generic SortedList.
static int cmpTI(const void *a, const void *b)
{
  return TimeIntervalCompare((TimeInterval *)a, (TimeInterval *)b);
}

// Create a SchedulingSequence capable of storing intervals.
// (Argument capacity is ignored!)
SchedulingSequence *SchedulingSequenceCreate(int capacity)
{
  assert(capacity >= 0);
  // You must allocate space for the struct and create an empty intervals list!
  SchedulingSequence *schedule = (SchedulingSequence *)malloc(sizeof(*schedule));
  if (schedule == NULL)
    return NULL;
  schedule->size = 0;
  List *intervals = ListCreate(cmpTI);
  if (intervals == NULL)
    return NULL;
  schedule->intervals = intervals;
  return schedule;
}

// Destroy SchedulingSequence *pss
void SchedulingSequenceDestroy(SchedulingSequence **pss)
{
  assert(*pss != NULL);
  free((*pss)->intervals);
  free(*pss);
  *pss = NULL;
}

int SchedulingSequenceIsEmpty(SchedulingSequence *ss)
{
  return ss->size == 0;
}

int SchedulingSequenceIsFull(SchedulingSequence *ss)
{
  return 0; // NEVER Full!
}

// Add interval *ti to *ss.
// Return true on success,
// return false if *ti overlaps any of the intervals in *ss.
int SchedulingSequenceAdd(SchedulingSequence *ss, TimeInterval *ti)
{
  assert(!SchedulingSequenceIsFull(ss));
  int res = ListInsert(ss->intervals, (void *)ti) == 0 ? 1 : 0;
  if(res) {
    ss->size++;
  }
  return res;
}

// Get the interval at position (idx) of *ss.
// idx=0 is the first position idx=ss->size-1 is the last position.
// Precondition: 0 <= idx < ss->size.
TimeInterval *SchedulingSequenceGet(SchedulingSequence *ss, int idx)
{
  assert(0 <= idx && idx < ss->size);
  ListMove(ss->intervals, idx);
  return (TimeInterval *)ListGetCurrentItem(ss->intervals);
}

// Remove the interval at position (idx) of *ss, and return it.
// idx=0 is the first position idx=ss->size-1 is the last position.
// Precondition: 0 <= idx < ss->size.
TimeInterval *SchedulingSequencePop(SchedulingSequence *ss, int idx)
{
  assert(0 <= idx && idx < ss->size);
  ss->size--;
  if (idx == 0) return (TimeInterval *)ListRemoveHead(ss->intervals);
  if (idx == ss->size) return(TimeInterval *)ListRemoveTail(ss->intervals);
  else
  {
    ListMove(ss->intervals, idx);
    return (TimeInterval *)ListRemoveCurrent(ss->intervals);
  }

}

// You may add auxiliary definitions and declarations here, if you need to.
