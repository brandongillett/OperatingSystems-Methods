#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"

typedef struct
{
  Stack    * stacks;
  unsigned   stacksSize;
} SomethingReallyImportant_Parameters;

static void * somethingReallyImportant(void * args)
{
  SomethingReallyImportant_Parameters * parameters = args;
  Stack * stacks      = parameters->stacks;
  unsigned stacksSize = parameters->stacksSize;

  struct random_data  randomNumberBuffer     = {0};
  char                randomNumberState[128] = {0};
  initstate_r( (uintptr_t)&randomNumberBuffer, randomNumberState, sizeof(randomNumberState), &randomNumberBuffer );

  int32_t theRandomNumber = 0;
  for (unsigned i = 0; i < 1000; ++i)
  {
    random_r( &randomNumberBuffer, &theRandomNumber );
    Stack * stack = stacks + (theRandomNumber % stacksSize);

    if( theRandomNumber%3 == 0 )   pop ( stack );
    else                           push( stack, theRandomNumber % (1<<12) );
  }

  return NULL;
}

int main(void)
{

  Stack          arrayOfStacks[] = {EmptyStack, EmptyStack, EmptyStack, EmptyStack};
  unsigned const size            = sizeof(arrayOfStacks)/sizeof(*arrayOfStacks);

  #define THREAD_COUNT 200u
  pthread_t thread_ids[ THREAD_COUNT ] = {0};

  SomethingReallyImportant_Parameters arguments = {arrayOfStacks, size};
  for( unsigned i = 0;  i != THREAD_COUNT;  ++i )   pthread_create( thread_ids+i, NULL, somethingReallyImportant, &arguments );

  for( unsigned i = 0;  i != THREAD_COUNT;  ++i )   pthread_join( thread_ids[i], NULL );

  for( unsigned i = 0; i<size; ++i )
  {
    Stack * stack = arrayOfStacks + i;
    printf("stack[%d] (%05d):  ", i, stack->_size);

    for(unsigned j = 0;  (j < 4) && (!isEmpty(stack));  ++j)   printf( "%5d, ", pop( stack ) );
    if( !isEmpty(stack) ) printf( "%5d\n", pop( stack ) );
  }

  printf("\nProgram completed successfully\n");
  return 0;
}
