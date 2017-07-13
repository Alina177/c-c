/*
 g++ -std=c++11  ph.cpp -lpthread
 */
#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream>
#include <queue>
#include <chrono>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mutex>

#define numper_philosopher 4
#define philosopher_sleep_time_min 6
#define philosopher_sleep_time_max 8

using namespace std;

void *eat(void* args);
int getRandValue(int,int);

mutex mutex_cout;
const int numper_fork = numper_philosopher;
mutex mutex_fork_p[numper_fork];		

int main(){

    pthread_t table_philosopher[numper_philosopher];

    int current_i[numper_philosopher];
    for (int i = 0; i < numper_philosopher; i++) {
    	current_i[i] = i;
    }

    for(int i = 0; i<numper_philosopher; i++){
        pthread_create(&(table_philosopher[i]),NULL,&eat,(void*)&current_i[i]);
        //usleep(getRandValue(philosopher_sleep_time_min, philosopher_sleep_time_max) * 1000 * 1000);
    }
    getchar();

    for( int i = 0; i<numper_philosopher; i++){
        pthread_cancel(table_philosopher[i]);
    }

return 0;

}

void *eat(void* args){
    int current_i = *(int*) args;
    int first_fork, second_fork,rand,value; 

    if( current_i != 0){
        first_fork = current_i-1;
    }else{
        first_fork = numper_fork-1;
    }
    second_fork = current_i;

    while(true){
    	rand = getRandValue(0,1);
    	if( rand == 0){
    		value = first_fork;
    		first_fork = second_fork;
    		second_fork = value;
    	}

    	mutex_cout.lock();
    		cout << "Philosopher " << current_i << " is trying to take first fork " << first_fork << endl;
    	mutex_cout.unlock();
    	if(mutex_fork_p[first_fork].try_lock() == 1){
    		mutex_cout.lock();
    			cout << "Philosopher " << current_i << " is trying to take second fork " << second_fork << endl;
    		mutex_cout.unlock();
			if(mutex_fork_p[second_fork].try_lock() == 1){
				mutex_cout.lock();
					cout << "Philosopher " << current_i << " is eating" << endl;
				mutex_cout.unlock();
				usleep(getRandValue(philosopher_sleep_time_min, philosopher_sleep_time_max) * 1000 * 1000);
				mutex_cout.lock();
    				cout << "Philosopher " << current_i << " is ended eating" << endl;
    			mutex_cout.unlock();
				mutex_fork_p[second_fork].unlock();
			}
    		mutex_fork_p[first_fork].unlock();
    	}
    	mutex_cout.lock();
    		cout << "Philosopher " << current_i << " is dreaming about life" << endl;
    	mutex_cout.unlock();
    	usleep(getRandValue(philosopher_sleep_time_min, philosopher_sleep_time_max) * 1000 * 1000);
	}
}

int getRandValue(int v1, int v2){
    return rand() % (v2 - v1 + 1) + v1;
}
