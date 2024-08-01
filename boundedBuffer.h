
#ifndef PROJECT3_BOUNDEDBUFFER_H
#define PROJECT3_BOUNDEDBUFFER_H
#include <vector>
#include <semaphore.h>
using namespace std;



class boundedBuffer {

private:

    vector <string> bbuffer;
    int tail;
    int head;
    int count;
    int CAPACITY;
    sem_t pcMutex;
    sem_t emptySlots;
    sem_t fullSlots;



public:


    boundedBuffer(size_t BUFFSIZE);
    void add(string& str);
    string remove();
    void producer(string n);
    void consumer();
    void print();
    ~   boundedBuffer();
};


#endif //PROJECT3_BOUNDEDBUFFER_H
