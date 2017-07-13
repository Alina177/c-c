/*
compile comand: g++ -o xfilename filename.cpp -lpthread -ltr
run programm: ./xfilename
*/
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define size_buffer 5
#define size_mutex 1
#define number_providers 3
#define number_consumers 4

#define provider_sleep_time_min 3
#define provider_sleep_time_max 5
#define consumer_sleep_time_min 4
#define consumer_sleep_time_max 6


struct QueueElement{
	int value;
	QueueElement* next;
};
struct Queue{
	Queue() {
		first = 0;
		last = 0;
	}
	QueueElement *first;
	QueueElement *last;
};

void *provider(void* args);
void *consumer(void* args);
void push(QueueElement *el);
QueueElement* pop();
int bufferLength();
int getRandValue(int, int);

Queue *buffer = new Queue;
sem_t mutex_provider;
sem_t mutex_consumer;
sem_t mutex_cout;
sem_t mutex_queue;
sem_t empty;
sem_t full;

int queue_element_counter = 0;

using namespace std;

int main(){

	sem_init(&mutex_provider, 0, size_mutex);
	sem_init(&mutex_consumer, 0, size_mutex);
	sem_init(&mutex_queue, 0, size_mutex);
	sem_init(&mutex_cout, 0, size_mutex);
	sem_init(&empty, 0, size_buffer);
	sem_init(&full, 0, 0);

/*	for (int i = 0; i< size_buffer; i++){
		sem_wait(&full);
	}
	int value0 = 0;
	sem_getvalue(&full, &value0);
	cout << "Value of full semaphore: " << value0 << endl;
*/
	cout << "Initialize semaphore" << endl;

	pthread_t thProviders[number_providers];
	pthread_t thConsumers[number_consumers];

	for (int i = 0; i<number_providers; i++){
		pthread_create(&(thProviders[i]), NULL, &provider, NULL);
		usleep(1000 * 1000);
	}
	for (int i = 0; i<number_consumers; i++){
		pthread_create(&(thConsumers[i]), NULL, &consumer, NULL);
		usleep(1000 * 1000);
	}
	getchar();
	for (int i = 0; i<number_providers; i++){
		pthread_cancel(thProviders[i]);
	}
	for (int i = 0; i<number_consumers; i++){
		pthread_cancel(thConsumers[i]);
	}
	return 0;
}

void push(QueueElement *el){
	if (buffer->last == 0){
		el->next = 0;
		buffer->first = el;
		buffer->last = el;
	}else{
		buffer->last->next = el;
		buffer->last = el;
		buffer->last->next = 0;
	}
}
QueueElement* pop(){
	QueueElement* element = new QueueElement;
	if (buffer->first != 0) {
		element = buffer->first;
		if (buffer->first->next == 0) {
			buffer->first = 0;
			buffer->last = 0;
		}else{
			buffer->first = buffer->first->next;
		}
	}
	else {
		element = 0;
	}
	return element;
}
int bufferLength() {
	int buf_length = 0; 
	if (buffer->first != 0) {
		QueueElement *current = buffer->first;
		while (current->next != 0) {
			buf_length++;
			current = current->next;
		}
	}
	return buf_length;
}
void *provider(void* args){
	while (true) {
		QueueElement *elem = new QueueElement;
		elem->value = queue_element_counter;
		queue_element_counter++;
		sem_wait(&empty);
			sem_wait(&mutex_provider);
				if( bufferLength() == 1){
					sem_wait(&mutex_queue);
					push(elem);
					sem_post(&mutex_queue);
				}else{
					push(elem);
				}
				sem_wait(&mutex_cout);
				
					cout << "Provider created new element with value " << elem->value << endl;
				sem_post(&mutex_cout);
			sem_post(&mutex_provider);
		sem_post(&full);
		usleep(getRandValue(provider_sleep_time_min, provider_sleep_time_max) * 1000 * 1000);
	}
}
void *consumer(void* args){
	while (true) {
		sem_wait(&full);
			sem_wait(&mutex_consumer);
				QueueElement *elem;
				if( bufferLength() == 1){
					sem_wait(&mutex_queue);
					elem = pop();
					sem_post(&mutex_queue);
				}else{
				elem = pop();
				}
			sem_post(&mutex_consumer);
		sem_post(&empty);
		sem_wait(&mutex_cout);
			cout << "Consumer took element with value " << elem->value << endl;
		sem_post(&mutex_cout);
		usleep(getRandValue(consumer_sleep_time_min, consumer_sleep_time_max) * 1000 * 1000);
	}
}
int getRandValue(int v1, int v2) {
	return rand() % (v2 - v1) + v1;
}