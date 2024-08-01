#include <iostream>
#include <semaphore.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <thread>
#include "boundedBuffer.h"
using namespace std;


void stageOne(boundedBuffer* buff);
void stageTwo(boundedBuffer*buff1, boundedBuffer* buff2);
void fileFilter(int filesize, int uid, int gid);


void errormsg(char * msg){
    perror(msg);
    exit(1);
}

int main() {
    /*
    int argc, char **argv
    int buffsize = atoi(argv[1]);
    int filesize= atoi(argv[2]);
    int uid = atoi(argv[3]);
    int gid = atoi(argv[4]);
    string string = argv[5];
*/


    int buffsize;
    int filesize;
    int uid;
    int gid;
    string string;
    boundedBuffer* bufferOne = new boundedBuffer( 25);
    boundedBuffer* bufferTwo = new boundedBuffer(25);

    vector<thread> th;
    th.emplace_back(stageOne,bufferOne);
    th.emplace_back(stageTwo,bufferOne, bufferTwo);

    // thread threadTwo(&fileFilter,filesize,uid,gid);
    th[0].join();
    th[1].join();
    //threadTwo.join();
    bufferTwo->print();
    free(bufferOne);
    free(bufferTwo);



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