/*
compile comand: g++ -o xfilename filename.cpp -lpthread -ltr
run programm: ./xfilename
*/
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <chrono>
#include <thread>

#include <mutex>


#define number_reader 4
#define number_writer 1
#define reader_sleep_time_min 2
#define reader_sleep_time_max 8
#define writer_sleep_time_min 2
#define writer_sleep_time_max 4

using namespace std;

mutex reader_mutex;
mutex writer_mutex;
mutex mutex_cout;
ofstream filestr_write;
ifstream filestr_read;

int r = 0;

int lock_reader;

void *writer(void* args);
void *reader(void* args);
int getRandValue(int,int);

int main(){
	pthread_t writer_thread[number_writer];
	pthread_t reader_thread[number_reader];

	int number_readers;

	for( int i = 0; i<number_writer; i++){
		pthread_create(&(writer_thread[i]), NULL, &writer, NULL);
		//usleep(getRandValue(writer_sleep_time_min, writer_sleep_time_max) * 10 * 10);
	}
	for( int i = 0; i<number_reader; i++){
		number_readers = i;
		pthread_create(&(reader_thread[i]), NULL, &reader,NULL);
		//usleep(getRandValue(reader_sleep_time_min, reader_sleep_time_max) * 10 * 10);
	}
	getchar();
	for( int i = 0; i<number_reader; i++){
		pthread_cancel(reader_thread[i]);
	}
	for( int i = 0; i<number_writer; i++){
		pthread_cancel(writer_thread[i]);
	}
    return 0;
}

void *reader(void* args){
	char inf[64];
	while(true){
		if( lock_reader == 1){
			usleep(getRandValue(reader_sleep_time_min, reader_sleep_time_max) * 1000 * 1000);
			continue;
		}
		reader_mutex.lock();
		if( r == 0){
			writer_mutex.lock();
		}
		r++;
		reader_mutex.unlock();
		mutex_cout.lock();
			cout << "Reader is reading: " << r << endl;
		mutex_cout.unlock();
		filestr_read.open("test.txt");
		filestr_read >> inf;
		filestr_write.close();
		mutex_cout.lock();
			cout << "Reader ended to read: " << inf << endl;
		mutex_cout.unlock();
		usleep(getRandValue(reader_sleep_time_min, reader_sleep_time_max) * 1000 * 1000);
		reader_mutex.lock();
		r--;
			if( r == 0){
				writer_mutex.unlock();
			}
		reader_mutex.unlock();
	}
}
void *writer(void* args){
	while(true){
		mutex_cout.lock();
			cout << "Writer came " << endl;
		mutex_cout.unlock();
		lock_reader = 1;
		writer_mutex.lock();
		lock_reader = 0;
		//filestr.open ("test.txt", fstream::out);
		mutex_cout.lock();
			cout << "Writer started to write " << endl;
		mutex_cout.unlock();
			filestr_write.open("test.txt");
			filestr_write << "foo " << 1000 << endl;
			filestr_write.close();
			usleep(getRandValue(writer_sleep_time_min, writer_sleep_time_max) * 1000 * 1000);
		mutex_cout.lock();
			cout << "Writer ended to write " << endl;
		mutex_cout.unlock();
	writer_mutex.unlock();
	usleep(getRandValue(writer_sleep_time_min, writer_sleep_time_max) * 1000 * 1000);
	//lock_reader = false;
	}
}
int getRandValue(int v1, int v2){
    return rand() % (v2 - v1 +1) + v1;
}
