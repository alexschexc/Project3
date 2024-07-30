//
// Created by Martin Arriaga on 7/30/24.
//

#include "boundedBuffer.h"
#include <thread>
#include <string>

#include <cmath>
#include <cstdlib>
#include <cassert>

#include <semaphore.h>
using namespace std;

boundedBuffer:: boundedBuffer(int BUFFSIZE){

    head = 0;
    tail = 0;
    count = 0;
    sem_init( &pcMutex, 0, 1 );
    sem_init( &emptySlots, 0, BUFFSIZE);
    sem_init( &fullSlots, 0, 0 );

}


/* Function used to add an item to the buffer */
void boundedBuffer:: add( void){

/* Reserve an empty slot */
sem_wait( &emptySlots );

/* Acquire the lock for critical section */
sem_wait( &pcMutex );

assert(count >= 0 && count <= BUFFSIZE);


/* insert the item at the tail end of the buffer */
buffer[tail] = number;
tail = (tail + 1) % BUFFSIZE;
++count;

cout << "Number added is " << number << endl;

/* Wake up a consumer */
sem_post( &fullSlots );

/* Release the lock for critical section */
sem_post( &pcMutex );


return;
}

/* Function used to remove an item from the buffer */
char boundedBuffer:: remove( void )
{

    /* Reserve a full slot */
    sem_wait( &fullSlots );


    /* Acquire the lock for critical section */
    sem_wait( &pcMutex );

    assert(count >= 0 && count <= CAPACITY);


    /* Delete an item at the head end of the buffer */
    int number = buffer[head];
    buffer[head] = 0;
    head = (head + 1) % CAPACITY;
    --count;

    assert( number > 0 );


    /* Wake up a producer */
    sem_post( &emptySlots );

    /* Release the lock for critical section */
    sem_post( &pcMutex );

    return number;
}

/* Driver code for a producer */
void boundedBuffer :: producer( void )
{
    while (1) {
        add( rand( ) % 100 +  1 );
    }
}

/* Driver code for a consumer */
void boundedBuffer :: consumer( void )
{
    while (1) {
        int number = remove( );

    }
}