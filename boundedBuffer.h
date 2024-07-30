//
// Created by Martin Arriaga on 7/30/24.
//

#ifndef PROJECT3_BOUNDEDBUFFER_H
#define PROJECT3_BOUNDEDBUFFER_H
#include <vector>
#include <semaphore.h>
using namespace std;

class boundedBuffer {
private:
    vector <char> buffer;
    int tail;
    int head;
    int count;
    sem_t pcMutex{};
    sem_t emptySlots{};
    sem_t fullSlots{};



public:


    boundedBuffer(int BUFFSIZE);
    void add();
    char remove();
    void producer();
    void consumer();

};


#endif //PROJECT3_BOUNDEDBUFFER_H
