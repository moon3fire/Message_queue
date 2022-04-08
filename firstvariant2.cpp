#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <iostream>

struct msg_buffer {
	long msg_type;
	int* msg_array;
	int size;
};

int main()
{
	msg_buffer* message;
	key_t key;
	int msg_id;

	key = ftok("msgfile" , 65);

	msg_id = msgget(key , 0666 | IPC_CREAT);

	msgrcv(msg_id , &message , sizeof(message) , 1 , 0);
	
	for(int i = 0 ; i < message->size ; ++i)
	{
		std::cout << message->msg_array[i] << " ";
	}
	std::cout << std::endl;
	
	msgctl(msg_id , IPC_RMID , NULL);
	return 0;
}
