#pragma once
#include <stdlib.h>
#include <pthread.h>

typedef struct StackNode StackNode;
typedef int    value_t;

typedef struct
{
  StackNode * _top;
  unsigned    _size;
  pthread_mutex_t mutex;
} Stack;

void    push     ( Stack * stack, value_t data );
value_t pop      ( Stack * stack               );
int     isEmpty  ( Stack * stack               );

extern const Stack EmptyStack;