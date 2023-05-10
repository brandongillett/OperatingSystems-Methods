#include <stdlib.h>
#include <assert.h>

#include "stack.h"

const Stack EmptyStack = {NULL, 0,PTHREAD_MUTEX_INITIALIZER};

struct StackNode
{
  value_t            _data;
  struct StackNode * _next;
};

static int isValid( Stack * stack )
{
  assert( stack );

  unsigned count = stack->_size;
  for(StackNode * current = stack->_top;  current;  current = current->_next)  --count;
  return count == 0;
}

void push( Stack * stack, value_t data )
{
  pthread_mutex_lock(&stack->mutex);
  assert( stack && isValid(stack) );
  StackNode * newNode = malloc( sizeof(StackNode) );
  newNode->_data = data;
  newNode->_next = stack->_top;
  stack->_top    = newNode;

  ++stack->_size;
  pthread_mutex_unlock(&stack->mutex);
}



value_t pop( Stack * stack )
{
  pthread_mutex_lock(&stack->mutex);
  assert( stack && isValid(stack) );
  if( isEmpty( stack ) )
  {
    pthread_mutex_unlock(&stack->mutex);
    return (value_t)0;
  }
  StackNode * temp = stack->_top;
  stack->_top      = stack->_top->_next;

  --stack->_size;
  pthread_mutex_unlock(&stack->mutex);
  value_t data = temp->_data;
  free( temp );
  return data;
}



int isEmpty( Stack * stack )
{
  assert( stack && isValid(stack) );
  return stack->_top == NULL;
}
