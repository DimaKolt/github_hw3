#ifndef __SEMAPHORE_H
#define __SEMAPHORE_H
#include "Headers.hpp"

// Synchronization Warm up 
class Semaphore {
public:
    Semaphore():counter(0),cond(),mutex(){}
    explicit Semaphore(unsigned val):counter(val),cond(),mutex(){}

    void down(){
        pthread_mutex_lock(&mutex);
        while (counter <= 0){
            //mutex unlock??
            pthread_cond_wait(&cond, &mutex);
        }
        counter--;
        pthread_mutex_unlock(&mutex);
    }

    void up(){
        pthread_mutex_lock(&mutex);
        pthread_cond_signal(&cond);
        counter++;
        pthread_mutex_unlock(&mutex);
    }
private:
	int counter;
	pthread_cond_t cond;
	pthread_mutex_t mutex;

};

#endif
