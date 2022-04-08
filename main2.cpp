#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <mqueue.h>

#define MAX_SIZE
#define MIN_ELEM -999999

struct msg_buffer {
	long type;
	int min_elem;
	int max_elem;
	int* msg_arr;
};

int main()
{
	msg_buffer message;
	key_t key;
	int msg_id;

	key = ftok("msgfile" , 65);
	msg_id = msgget(key , 0666 | IPC_CREAT);
	
	unsigned long priority = 0;
	mq_attr attr{};
	mq_getattr(msg_id, &attr);
	message.msg_arr = (int*)malloc(attr.mq_msgsize);

	msgrcv(msg_id , message.msg_arr , attr.mq_msgsize , &priority);

	for(int i = 0 ; ; ++i)
	{
		if(message.msg_arr[i] == MIN_ELEM)
			break;
		printf("%d\n" , message.msg_arr[i]); 
	}

	msgctl(msg_id , IPC_RMID , NULL);

	return 0;
}
