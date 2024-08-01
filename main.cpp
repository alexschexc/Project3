#include <iostream>
#include <fstream>
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
void stageOne(boundedBuffer* buff);
void stageTwo(boundedBuffer* source,boundedBuffer* destination );
void errormsg(char* msg){
    perror(msg);
    exit(1);
}
/* The main function */
int main( void )
{
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
     for(int i = 0; i < buffsize; ++i){ // loop 2 or sub loop 1?
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
   
   
   //////////////
   /* Stage 3 */
   /////////////
   for(int j = 0; j < buffsize; ++j){  // 1.Start Loop3 ? 
     filename = bufferTwo[j];
     if(filename != nullptr && filename[0] != '\0'){
       ifstream file (filename);
       if(!file.is_open()){
	 cerr << "Error opening file: " << filename << endl;
	 exit(1);
       }
       std::string line = "";
       while (getline(file, line)){
	 bufferThree.push(line); // change push to whatever our boundedBuffer add function is
       }
       file.close(); // the file will be reopened on the next pass through, seems like it has to be done this way otherwise ifstream won't know which filename we're referencing.
     }
   }
   //////////////
   /* Stage 4 */
   /////////////
   for(int k = 0; k < buffsize; ++k){   // 1.Start Loop 4}

   //////////////
   /* Stage 5 */
   /////////////  
   for(int k = 0; k < buffsize; ++k) {   // 1.Start Loop 5}

       /* Destroy the semaphores */
       sem_destroy(&pcMutex);
       sem_destroy(&emptySlots);
       sem_destroy(&fullSlots);

       return 0;

   }

 void stageOne(boundedBuffer* buff){
           DIR *directory;
           struct dirent *entry;

           if( (directory = opendir("/Users/martinarriaga/Desktop/TestDirectory")) != NULL){

               while( (entry= readdir(directory)) != NULL){
                   if( entry->d_type == DT_REG ){
                       string filename = entry->d_name;
                       buff->add( filename);

                   }else {

                   }
               }
               closedir(directory);

           }else{
               errormsg("Could not access Directory");
           }

       }

       void stageTwo(boundedBuffer* buffer1,boundedBuffer* buffer2 ){
           int h = 1000;
           while(h > 0){
               string str = buffer1->remove();
               buffer2 ->add(str);
               h--;

           }

       }
