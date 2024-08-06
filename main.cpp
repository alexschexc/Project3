#include <iostream>

#include <dirent.h>
#include <string>
#include <stdio.h>
#include <thread>
#include "boundedBuffer.h"
#include <fstream>


using namespace std;


void stageOne(boundedBuffer* buff);
void stageTwo(boundedBuffer* buff1, boundedBuffer* buff2);
void stageThree(boundedBuffer* buff2, boundedBuffer* buff3);
void stageFour(boundedBuffer* buffer3, boundedBuffer* buffer4);



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
    boundedBuffer* bufferOne  = new boundedBuffer( 50);
    boundedBuffer* bufferTwo = new boundedBuffer(50);
    boundedBuffer* bufferThree = new boundedBuffer(50);



    vector<thread> th;
    th.emplace_back(stageOne,bufferOne);
    th.emplace_back(stageTwo,bufferOne, bufferTwo);
    th.emplace_back(stageThree, bufferTwo, bufferThree);


    // thread threadTwo(&fileFilter,filesize,uid,gid);
    for (auto& threads: th){
        threads.join();
    }


    free(bufferOne);
    free(bufferTwo);
    free(bufferThree);

    return 0;
}

void stageOne(boundedBuffer* buff) {
    DIR *directory;
    dirent *entry;

    if ((directory = opendir(".")) != NULL) {

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


    buff->add((string &) "\n");
}

void stageTwo(boundedBuffer* buffer1, boundedBuffer* buffer2){

    while(true){
        string str = buffer1->remove();
        if(str.empty()){
            break;
        }
        buffer2 ->add(str);

    }
    buffer2 ->add((string &) "\n");

}


void stageThree(boundedBuffer* buffer2, boundedBuffer* buffer3){

    while(true){
        string filename = buffer2 ->remove();
        cout<< filename;

        if(filename.empty()){
            break;
        }

        ifstream file;
        file.open(filename);
        if(!file){
            //do nothing
        }else{
            string line;
            while (getline(file, line)){
                cout << line << endl;
                buffer3->add(line);
                file.close();
            }

            file.close();
        }

    }}

void stageFour(boundedBuffer* buffer3, boundedBuffer* buffer4){

}