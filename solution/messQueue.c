#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>

#define BYTENUM 1024

int main()
{
	mqd_t messageQueue;
	struct mq_attr queueAttributes;
	char buffer[BYTENUM + 1];
	int end = 0;

	queueAttributes.mq_flags = 0;
	queueAttributes.mq_maxmsg = 10;
	queueAttributes.mq_msgsize = 1024;
	queueAttributes.mq_curmsgs = 0;

	messageQueue = mq_open("/DavidsQue", O_CREAT, | O_RDONLY, 0644, &queueAttributes);

	do
	{
		ssize_t bytes_read;

		bytes_read = mq_receive(messageQueue, buffer, 1024, NULL);

		buffer[bytes_read] = '\0';

		if(! strncmp(buffer, "exit", strlen("exit")))
		{
			end = 1;
		}
		else
		{
			printf("Message successfully received: %s\n", buffer);
		}
	}
	while(!end);

	mq_close(messageQueue);
	mq_unlink("/DavidsQue");

	return 0;

}