#include <iostream>
#include <thread>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <errno.h>


#include <cmath>
#include <cstdlib>
#include <cassert>

#include <semaphore.h>
#include <dirent.h>
#include <string.h>
#include "boundedBuffer.h"


using namespace std;

/* Data structure for storing the items produced until consumed */

/* Capacity of the bounded buffer */
const int CAPACITY = 25;

/* Array to store items - used to implement a FIFO queue using circular buffer */
int buffer[CAPACITY];

/* The two endpoints of the queue */
int tail;
int head;

/* Number of items currently in the buffer */
int count;

/* Number of producers and consumers in the system */
const int PRODUCERS = 1;
const int CONSUMERS = 1;

/* Arrays to store producer and consumer threads */
thread producers[PRODUCERS];
thread consumers[CONSUMERS];

/* Variables for process synchronization */

/* A semaphore to provide mutual exclusion */
sem_t pcMutex;

/* Semaphores for producer(s) and concumer(s) to synchronize with each other */
sem_t emptySlots;
sem_t fullSlots;

/* Function used to add an item to the buffer */

void add( int number );
int remove( void ); 
void producer( void );
void consumer( void );
void stageOne();
void errormsg(char* msg){
    perror(msg);
    exit(1);
}
/* The main function */
int main( void )
{
  stageOne();
    int argc; char **argv;
    int buffsize = atoi(argv[1]);
    int filesize= atoi(argv[2]);
    int uid = atoi(argv[3]);
    int gid = atoi(argv[4]);
    string string = argv[5];

 
   /* Initialize the buffer */
   for(int i = 0; i < CAPACITY; ++i )
   {
      buffer[i] = 0;
   }

   /* Initialize the variables associated with the buffer */
   head = 0;
   tail = 0;
   count = 0;

   /* Initialize the semaphores */
   sem_init( &pcMutex, 0, 1 );
   sem_init( &emptySlots, 0, CAPACITY );
   sem_init( &fullSlots, 0, 0 );

   /* Create producer and consumer threads */
   for( int i = 0; i < PRODUCERS; ++i )
   {
      producers[i] = thread ( producer );
   }
   for( int i = 0; i < CONSUMERS; ++i )
   {
      consumers[i] = thread ( consumer );
   }

   /* Wait for all threads to terminate */
   for( int i = 0; i < PRODUCERS; ++i )
   {
      producers[i].join( );
   }
   for( int i = 0; i < CONSUMERS; ++i )
   {
      consumers[i].join( );
   }

//   for(int i = 0; i < buffsize; ++i){  // 1. Start Loop1
   //////////////
   /* Stage 1 */
   /////////////  




   //////////////
   /* Stage 2 */
   ///////////// 
   char* filename;


   if(filesize == -1 &&uid == -1 && gid == -1){
	 // read from bufferOne
	 // no filtering occurs
	 // write to bufferTwo
   }
   else{
     int uID, gID, fSize = 0;
     for(int i = 0; i < buffsize; ++i){
       struct stat fileStat;
       filename = bufferOne[i];
       if (stat(filename, &fileStat) == -1){
	 cerr << "Error retrieving file information: " << strerror(errno) << endl;
       }
       fSize = fileStat.st_size;
       uID = fileStat.st_uid;
       gID = fileStat.st_gid;
       
       if( uid == -1 && gid ==-1 ){
	 if (fSize > filesize){
	   // read from bufferOne[i]
	   // push to bufferTwo[]
	 }
	 else continue;
       }
       else if( filesize == -1 && uid ==-1 ){
	 if (gID == gid){
	   // read from bufferOne[i]
	   // push to bufferTwo[]
	 }
	 else continue;
       }
       else if( filesize == -1 && gid ==-1 ){
	 if (uID == uid){
	   // read from bufferOne[i]
	   // push to bufferTwo[]
	 }
	 else continue;
       }
       else if( filesize == -1 ){
	 if (uID == uid && gID == gid){
	   // read from bufferOne[i]
	   // push to bufferTwo[]
	 }
	 else continue;

       }
       else if( uid ==-1 ){
	 if (fSize > filesize && gID == gid ){
	   // read from bufferOne[i]
	   // push to bufferTwo[]
	 }
	 else continue;
       }
       else if( gid ==-1 ){	 
	 if (fSize > filesize && uID == uid ){
	   // read from bufferOne[i]
	   // push to bufferTwo[]
	 }
	 else continue;}
       else{
	 if (fSize > filesize && uID == uid && gID == gid ){
	   // read from bufferOne[i]
	   // push to bufferTwo[]
	 }
	 else continue;}


       }
       

     }
   
   }
   
   //////////////
   /* Stage 3 */
   /////////////
   
//   for(int j = 0; j < buffsize; ++j){  // 1.Start Loop2  

   //////////////
   /* Stage 4 */
   /////////////
   
//   for(int k = 0; k < buffsize; ++k){   // 1.Start Loop 3

   //////////////
   /* Stage 5 */
   /////////////
     
     //}
    // }
  // }


   /* Destroy the semaphores */
   sem_destroy( &pcMutex );
   sem_destroy( &emptySlots );
   sem_destroy( &fullSlots );

   return 0;
}
void stageOne(){
    DIR *directory;
    dirent *entry;

    if( (directory = opendir("/Users/martinarriaga/Desktop/TestDirectory")) != NULL){
        int x =0;
        while( (entry= readdir(directory)) != NULL){
            if( !(strcmp(entry->d_name, ".")) || !(strcmp(entry->d_name,"..")) ){

            }else {

                bufferOne[x] = entry->d_name;
                x++;

            }
        }
        closedir(directory);

    }else{
        errormsg("Could not access Directory");
    }
}

void add( int number ) 
{

   /* Reserve an empty slot */
   sem_wait( &emptySlots );

   /* Acquire the lock for critical section */
   sem_wait( &pcMutex );

   assert(count >= 0 && count <= CAPACITY);
   

   /* insert the item at the tail end of the buffer */
   buffer[tail] = number;
   tail = (tail + 1) % CAPACITY;
   ++count;

   cout << "Number added is " << number << endl;

   /* Wake up a consumer */
   sem_post( &fullSlots );
   
   /* Release the lock for critical section */
   sem_post( &pcMutex );


   return;
}

/* Function used to remove an item from the buffer */
int remove( void ) 
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
   
   cout << "Number removed is " << number << endl;

   /* Wake up a producer */
   sem_post( &emptySlots );
 
   /* Release the lock for critical section */
   sem_post( &pcMutex );

   return number;
}

/* Driver code for a producer */
void producer( void )
{
   while (1) {
      add( rand( ) % 100 +  1 );
   }
}

/* Driver code for a consumer */
void consumer( void )
{
   while (1) {
      int number = remove( );
	  
   }
} 
