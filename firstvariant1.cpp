#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>

struct msg_buffer {
	long msg_type;
	int size = 0;
	int msg_arr[1];
};

int main()
{
	std::cout << "Enter array elements count" << std::endl;
	int size;
	std::cin >> size;
	
	std::cout << "Now enter array elements" << std::endl;	
	int temp_arr[size];
	for(int i = 0 ; i < size ; ++i)
	{
		std::cin >> temp_arr[i];
	}
	
	struct msg_buffer* buf = (msg_buffer*)malloc(sizeof(struct msg_buffer) + sizeof(int)*size + 1);
	buf->msg_type = 1;
	buf->size = size;
	for(int i = 0 ; i < size ; ++i)
	{
		buf->msg_arr[i] = temp_arr[i];
	}

	for(int i = 0 ; i < size ; ++i)
	{
		std::cout << buf->msg_arr[i];
	}


	key_t key;
	int msg_id;
	
	key = ftok("msgfile" , 65);
	msg_id = msgget(key , 0666 | IPC_CREAT);
	
	msgsnd(msg_id , buf , sizeof(int) * (size + 1) , 0);
	
	return 0;
}
