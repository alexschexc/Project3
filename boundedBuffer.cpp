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
#include <vector>
using namespace std;


boundedBuffer:: boundedBuffer(size_t BUFFSIZE):
        head(0),tail(0),count(25),bbuffer(BUFFSIZE), pcMutex(1), emptySlots(BUFFSIZE), fullSlots(0), CAPACITY(BUFFSIZE)
{

}





/* Function used to add an item to the buffer */
void boundedBuffer:: add( string& str){

/* Reserve an empty slot */
    sem_wait( &emptySlots );

/* Acquire the lock for critical section */
    sem_wait( &pcMutex );

    assert(count >= 0 && count <= CAPACITY);


/* insert the item at the tail end of the buffer */
    bbuffer.at(tail ) = str ;
    tail = (tail + 1) % CAPACITY;
    ++count;



/* Wake up a consumer */
    sem_post( &fullSlots );

/* Release the lock for critical section */
    sem_post( &pcMutex );


    return;
}

/* Function used to remove an item from the buffer */
string boundedBuffer:: remove()
{

    /* Reserve a full slot */
    sem_wait( &fullSlots );


    /* Acquire the lock for critical section */
    sem_wait( &pcMutex );

    assert(count >= 0 && count <= CAPACITY);


    /* Delete an item at the head end of the buffer */
    string filename = bbuffer.at(head);
    //bbuffer.at(head) = nullptr;
    head = (head + 1) % CAPACITY;
    --count;

    //assert(filename != nullptr);


    /* Wake up a producer */
    sem_post( &emptySlots );

    /* Release the lock for critical section */
    sem_post( &pcMutex );

    return filename;
}

/* Driver code for a producer */
void boundedBuffer :: producer( string x )
{
    while (1) {

        //add( x);
    }
}

/* Driver code for a consumer */
void boundedBuffer :: consumer( void )
{
    while (1) {
        string number = remove( );

    }
}

void boundedBuffer::print(){
    for(int i =0; i < 3; i++){
        fprintf(stdout, "%s\n",bbuffer[i].c_str());

    }

}

boundedBuffer::~boundedBuffer() {
    sem_destroy(&pcMutex);
    sem_destroy(&emptySlots);
    sem_destroy(&fullSlots);

}