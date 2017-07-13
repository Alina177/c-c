file:
	producer_consumer.cpp
		------->The problem of the producer and the consumer

		Synchronization and interaction of processes and flows.
		* using objects of semaphore and threads;
		*task: Two processes share a buffer of a limited size. One of them, the manufacturer, puts the data in this buffer, and the other, the consumer, reads them from there. The problem can be generalized to the case of m producers and n consumers.

	philosopher.cpp
		------->The Problem of Diner Philosophers

		Modeling processes competing for exclusive access to a limited number of resources (for example, Input / Output devices).
		* using objects of mutex and threads;
		*task: There are N philosophers sitting at a round table. Before each of them is a plate with spaghetti. Spaghetti is so slippery that each philosopher needs two forks to manage with. Between each two plates lies one fork.
		The life of a philosopher consists of alternating periods of food intake and reflection (the remaining processes of life are inessential in this case). When a philosopher is hungry, he tries to get two forks, left and right, in any order. If he managed to get two forks, he eats for a while, then puts the forks and continues thinking.

	writer_reader.cpp
		------->The problem of readers and writers

		Model access to the database.
		* using mutex and threads;
		*task: It is necessary to provide exclusive access to the database to the process that performs data recording and multiple access to processes that perform data reading. Giving priority to the writer process.

	bradobrey.cpp
		------->The problem of a sleeping barber.

		* using semaphore and threads;
		*task: There is one process-barber, his chair and N chairs for the processes of "customers." If there are no customers, the barber sleeps in his chair. If a "client" comes to the hairdresser's, he must wake up the "barber". If a client comes and sees that the barber is busy, he either takes one of the chairs (if there is room) or leaves (if there is no place). It is necessary to program barber and customers so as to avoid competition.