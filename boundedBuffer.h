#ifndef PROJECT3_BOUNDEDBUFFER_H
#define PROJECT3_BOUNDEDBUFFER_H
#include <vector>
#include <semaphore>
#include <string>
#include <libc.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/stat.h>

using namespace std;


class boundedBuffer {

private:

    vector <string> bbuffer;
    int tail;
    int head;
    int count;
    int CAPACITY;

    sem_t* pcMutex;
    sem_t* emptySlots;
    sem_t* fullSlots;






public:

    explicit boundedBuffer(int BUFFSIZE);
    void add(string& str);
    string remove();
    void producer(string n);
    void consumer();
    void print();
    ~boundedBuffer();
};


#endif //PROJECT3_BOUNDEDBUFFER_H
