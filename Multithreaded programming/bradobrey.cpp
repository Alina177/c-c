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
#define number_chair 6
#define number_client 4
#define number_bradobrey 1

#define thread_sleep_time_min 3
#define thread_sleep_time_max 5
#define bradobrey_sleep_time_min 4
#define bradobrey_sleep_time_max 6

using namespace std;

struct QueueElement{
	QueueElement(){
		sem_init(&mutex_client, 0, 1);
		sem_wait(&mutex_client);
	}

	int value;
	QueueElement* next;
	sem_t mutex_client;
};
struct Queue{
	Queue() {
		first = 0;
		last = 0;
	}
	QueueElement *first;
	QueueElement *last;
};

void *bradobrey(void* args);
void *client(void* args);
void push(QueueElement *el);
QueueElement* pop();
int bufferLength();
int getRandValue(int, int);

Queue *buffer = new Queue;
sem_t mutex_bradobrey;
sem_t mutex_cout;
sem_t mutex_queue;
sem_t mutex_queue1;
sem_t semaphore_chair;

int queue_element_client = 0;

int main(){
	sem_init(&mutex_bradobrey, 0, size_mutex);
	sem_init(&mutex_queue, 0, size_mutex);
	sem_init(&mutex_queue1, 0, size_mutex);
	sem_init(&mutex_cout, 0, size_mutex);
	sem_init(&semaphore_chair, 0, number_chair);
	//sem_init(&mutex_client, 0, size_mutex);
	cout << "Initialize semaphore" << endl;

	pthread_t thBradobrey[number_bradobrey];
	pthread_t thClient[number_client];

    pthread_create(&(thBradobrey[0]), NULL, &bradobrey, NULL);
	usleep(2000 * 1000);
	for (int i = 0; i<number_client; i++){
		pthread_create(&(thClient[i]), NULL, &client, NULL);
		usleep(1000 * 1000);
	}
	getchar();
	for (int i = 0; i<number_bradobrey; i++){
		pthread_cancel(thBradobrey[i]);
	}
	for (int i = 0; i<number_client; i++){
		pthread_cancel(thClient[i]);
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
void *client(void* args){
	while(true){
        sem_wait(&mutex_queue);

		int value0 = 0;
		/* 1*/
		sem_getvalue(&semaphore_chair, &value0);
		//cout << value0 << " value" << endl;
		//cout << queue_element_client << " queue_element_client" << endl;

		if(value0 == 0 /*number_chair*/){
			/**/
			sem_post(&mutex_queue);
			sem_wait(&mutex_cout);
                cout << "No place for new client" << endl;
            sem_post(&mutex_cout);
			usleep(getRandValue(thread_sleep_time_min, thread_sleep_time_max) * 5000 * 1000);
			continue;
		}else{
			sem_wait(&semaphore_chair);
			sem_wait(&mutex_cout);
                cout << "New client took his place" << endl;
            sem_post(&mutex_cout);


			QueueElement *client = new QueueElement;
			client->value = queue_element_client;
			push(client);


			/**/
			if(queue_element_client == 0){
				sem_wait(&mutex_cout);
                    cout << "First client woke up bradobrey" << endl;
				sem_post(&mutex_cout);

				sem_post(&mutex_bradobrey);
			}

			queue_element_client++;
			sem_post(&mutex_queue);


			sem_wait(&client->mutex_client);

			//2
			sem_wait(&mutex_cout);
				cout << "Client " << client->value << " is huircuted " << endl;
			sem_post(&mutex_cout);
			//1
			sem_wait(&mutex_queue);
				queue_element_client--;
			sem_post(&mutex_queue);

			usleep(getRandValue(thread_sleep_time_min, thread_sleep_time_max) * 3000 * 1000);
		}
	}
}
void *bradobrey(void* args){
	while (true) {
		/*!*/
		//sem_wait(&mutex_queue);
		if(queue_element_client == 0){
			//sem_post(&mutex_queue);/*!*/
			sem_wait(&mutex_cout);
                cout << "Bradobrey is sleeping" << endl;
			sem_post(&mutex_cout);

			sem_wait(&mutex_bradobrey);
		}
		sem_wait(&mutex_bradobrey);

		//1
		sem_wait(&mutex_queue1);
			QueueElement * first_client = pop();
		sem_post(&mutex_queue1);
		//2
		sem_wait(&mutex_cout);
			cout << "Start haircut with client " << first_client->value << endl;
		sem_post(&mutex_cout);

		usleep(getRandValue(thread_sleep_time_min, thread_sleep_time_max) * 1000 * 1000);

		sem_wait(&mutex_cout);
			cout << "Place is empty" << endl;
		sem_post(&mutex_cout);

		sem_post(&first_client->mutex_client);
        usleep(100 * 1000);
		sem_post(&semaphore_chair);

		sem_post(&mutex_bradobrey);
	}
}
int getRandValue(int v1, int v2) {
	return rand() % (v2 - v1) + v1;
}
