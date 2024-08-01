
#ifndef PROJECT3_BOUNDEDBUFFER_H
#define PROJECT3_BOUNDEDBUFFER_H
#include <vector>
#include <semaphore.h>
#include <string>
using namespace std;



class boundedBuffer {

private:

    int head;
    int tail;
    int count;
    vector <string> bbuffer;
    sem_t pcMutex;
    sem_t emptySlots;
    sem_t fullSlots;
    int CAPACITY;



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
