//
// Created by Dima on 19/12/2018.
//

#include "semaphore.hpp"
Semaphore::Semaphore():counter(0),cond(),mutex(){}
Semaphore::Semaphore(unsigned val):counter(val),cond(),mutex(){}

void Semaphore::down(){
    pthread_mutex_lock(&mutex);
    while (counter <= 0)
        pthread_cond_wait(&cond,&mutex);
    counter--;
    pthread_mutex_unlock(&mutex);
}

void Semaphore::up(){
    pthread_mutex_lock(&mutex);
    pthread_cond_signal(&cond);
    counter++;
    pthread_mutex_unlock(&mutex);
}
