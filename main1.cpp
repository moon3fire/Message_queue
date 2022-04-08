#include <iostream>
#include <cstdint>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#define MAX_SIZE 1024
#define MIN_ELEM -999999

struct msg_buffer {
	long type;
	int min_elem;
	int max_elem;
	int msg_arr[MAX_SIZE];
};

int main()
{
	puts("Enter array size");
	int size;
	std::cin >> size;

	msg_buffer message;
	message.msg_arr[size + 1] = MIN_ELEM;

	puts("Now enter array elements");
	for(int i = 0 ; ; ++i)
	{
		if(message.msg_arr[i+1] == MIN_ELEM)
			break;
		scanf("%d" , &message.msg_arr[i]);
	}

	for(int i = 0 ; i < size ; ++i)
	{
		printf("%d\n" , message.msg_arr[i]);
	}
	std::cout << std::endl;

	message.type = 1;
	key_t key;
	int msg_id;

	key = ftok("msgfile" , 65);
	msg_id = msgget(key , 0666 | IPC_CREAT);

	msgsnd(msg_id , &message , sizeof(message) , 0);


	return 0;
}
