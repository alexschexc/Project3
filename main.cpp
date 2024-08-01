#include <iostream>
#include <semaphore.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <thread>
#include "boundedBuffer.h"
#include <fstream>

using namespace std;


void stageOne(boundedBuffer* buff);
void stageTwo(boundedBuffer*buff1, boundedBuffer* buff2);
void stageThree(boundedBuffer*buff2, boundedBuffer* buff3);



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
    boundedBuffer* bufferOne = new boundedBuffer( 50);
    boundedBuffer* bufferTwo = new boundedBuffer(50);
    boundedBuffer* bufferThree = new boundedBuffer(50);

    // vector<thread> th;
    // th.emplace_back(stageOne,bufferOne);
    // th.emplace_back(stageTwo,bufferOne, bufferTwo);
    //th.emplace_back(stageThree, bufferTwo, bufferThree);
    thread t1(stageOne,bufferOne);
    thread t2(stageTwo,bufferOne, bufferTwo);
    thread t3(stageThree, bufferTwo, bufferThree);


    // thread threadTwo(&fileFilter,filesize,uid,gid);
    //for (auto& threads: th){
    //     threads.join();
    // }
    t1.join();
    t2.join();
    t3.join();
    //bufferOne->print();
    // bufferTwo->print();
    bufferThree->print();
    free(bufferOne);
    free(bufferTwo);
    free(bufferThree);

    return 0;
}

void stageOne(boundedBuffer* buff) {
    DIR *directory;
    struct dirent *entry;

    if ((directory = opendir("/Users/martinarriaga/CLionProjects/pipeGREP")) != NULL) {

        while ((entry = readdir(directory)) != NULL) {
            if (entry->d_type == DT_REG) {
                string filename = entry->d_name;
                buff->add(filename);

            }

        }
        closedir(directory);

    } else {
        errormsg("Could not access Directory");
    }

    string blank = "\n";
    buff->add(blank);
}

void stageTwo(boundedBuffer* buffer1, boundedBuffer* buffer2 ){
    int h = 1000;
    while(h > 0){
        string str = buffer1->remove();
        buffer2 ->add(str);
        h--;

    }

}










void stageThree(boundedBuffer* buffer2, boundedBuffer* buffer3){
    int h = 1000000;
    while(h>0){

        string filename = buffer2 ->remove();
        fprintf(stdout," %s\n", filename.c_str());

        // if(filename.empty()){
        // fprintf(stdout," failurerr %s\n", filename.c_str());
        // buffer3->print();
        // break;
        // }
        ifstream file;
        file.open(filename);

        // if(!file){
        //   fprintf(stdout," failure2 %s\n");
        // break;
        //}

        string line;
        while (getline(file, line)){
            buffer3->add(line); // change push to whatever our boundedBuffer add function is
        }
        file.close();
        // the file will be reopened on the next pass through, seems like it has to be done this way otherwise ifstream won't know which filename we're referencing.
        h--;
    }


}