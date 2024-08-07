
#include "boundedBuffer.h"
#include <string>
#include <cmath>
#include <cassert>
#include <iostream>
#include <semaphore.h>
#include <fcntl.h>




using namespace std;


boundedBuffer :: boundedBuffer(int BUFFSIZE):
        head(0),tail(0),count(0),bbuffer(BUFFSIZE), CAPACITY(BUFFSIZE)
{
    pcMutex = sem_open("pcMutex",O_CREAT,0644,1);
    fullSlots = sem_open("fullSlots", O_CREAT,0664,0);
    emptySlots = sem_open("emptySlots", O_CREAT,0644,BUFFSIZE);
    if( pcMutex == SEM_FAILED || fullSlots == SEM_FAILED || emptySlots == SEM_FAILED ){
        sem_close(pcMutex);
        sem_close(fullSlots);
        sem_close(emptySlots);
        sem_unlink("pcMutex");
        sem_unlink("fullSlots");
        sem_unlink("emptySlots");
    }


}

/* Function used to add an item to the buffer */
void boundedBuffer:: add( string& str){

/* Reserve an empty slot */
    sem_wait(emptySlots);

/* Acquire the lock for critical section */
    sem_wait(pcMutex );

//assert(count >= 0 && count <= CAPACITY);


/* insert the item at the tail end of the buffer */
    bbuffer[tail] = str ;
    tail = (tail + 1) % CAPACITY;
    ++count;



/* Wake up a consumer */
    sem_post( fullSlots );

/* Release the lock for critical section */
    sem_post( pcMutex );


    return;
}

/* Function used to remove an item from the buffer */
string boundedBuffer:: remove()
{

    /* Reserve a full slot */
    sem_wait( fullSlots );


    /* Acquire the lock for critical section */
    sem_wait( pcMutex );

    //assert(count >= 0 && count <= CAPACITY);


    /* Delete an item at the head end of the buffer */
    string filename = bbuffer[head];
    //bbuffer[head]="\n";
    head = (head + 1) % CAPACITY;
    --count;

    //assert(filename.empty());


    /* Wake up a producer */
    sem_post( emptySlots );

    /* Release the lock for critical section */
    sem_post( pcMutex );

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
    for(int i =0; i <200; i++){
        cout << bbuffer[i] << endl;
    }

}

boundedBuffer::~boundedBuffer() {
    sem_close(pcMutex);
    sem_close(fullSlots);
    sem_close(emptySlots);
    sem_unlink("pcMutex");
    sem_unlink("fullSlots");
    sem_unlink("emptySlots");

}
