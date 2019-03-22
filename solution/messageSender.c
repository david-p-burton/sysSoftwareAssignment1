#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>

#include "messageSender.h"

void messageSender(char message[])
{
	mqd_t messageQ;

	messageQ = mq_open("/DavidsQue", O_WRONLY);

	mq_send(messageQ, message, 1024, 0);
	mq_close(messageQ);
}