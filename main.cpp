#include <iostream>
#include <dirent.h>
#include <string>
#include <stdio.h>
#include <thread>
#include "boundedBuffer.h"
#include <fstream>
#include <libc.h>
#include <cstring>



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


    int buffsize = 50;
    int filesize;
    int uid;
    int gid;
    string string;
    boundedBuffer*  bufferOne  = new boundedBuffer( buffsize);
    boundedBuffer* bufferTwo = new boundedBuffer(buffsize);
    boundedBuffer* bufferThree = new boundedBuffer(buffsize);



    vector <thread> th;
    th.emplace_back(stageOne,bufferOne);
    th.emplace_back(stageTwo,bufferOne, bufferTwo);
    th.emplace_back(stageThree, bufferTwo, bufferThree);


    // thread threadTwo(&fileFilter,filesize,uid,gid);
    for (auto& threads: th){
        threads.join();
    }


    delete(bufferOne);
    delete(bufferTwo);
    delete(bufferThree);

    return 0;
}

void stageOne(boundedBuffer* buff) {
    DIR *directory;
    dirent *entry;

    if( (directory = opendir(".")) != NULL){

        while( (entry= readdir(directory)) != NULL){
            if( !(strcmp(entry->d_name, ".")) || !(strcmp(entry->d_name,"..")) ){

            }else {
                string str =entry->d_name;
                //cout << str << endl;
                buff->add(str);
            }
        }
        closedir(directory);

    }else{
        errormsg("Could not access Directory");
    }

    string key ( "alldone6969");
    buff->add(key);

}

void stageTwo(boundedBuffer* buffer1, boundedBuffer* buffer2){
    string key ( "alldone6969");
    while(true){
        string str = buffer1->remove();
        //cout << str << endl;
        if(!(str.compare(key))){
            buffer2 ->add(key);
            break;
        }
        buffer2 ->add(str);
    }
    buffer2 ->add(key);


}


void stageThree(boundedBuffer* buffer2, boundedBuffer* buffer3){
    string key ("alldone6969");
    while(true){
        string filename = buffer2 ->remove();

        if(!(filename.compare(key))){
            buffer2 ->add(key);
            break;
        }

        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            buffer3->add(line);
        }
        file.close();
    }
}

void stageFour(boundedBuffer* buffer3, boundedBuffer* buffer4){


}