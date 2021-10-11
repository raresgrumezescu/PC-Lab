#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "lib.h"

#define HOST "127.0.0.1"
#define PORT 10001

char sum(msg r) {
	char ans = 0;
	for(int i = 0; i < r.len - 1; i++) {
		ans ^= r.payload[i];
	}
	return ans;
}

int main(void)
{
	msg r;
	int i, res;
	printf("[RECEIVER] Starting.\n");
	init(HOST, PORT);
	int count = 0;
	for (i = 0; i < COUNT; i++) {
		/* wait for message */
		res = recv_message(&r);
		if (res < 0) {
			perror("[RECEIVER] Receive error. Exiting.\n");
			return -1;
		}
		if(sum(r) != r.payload[MSGSIZE - 1]) {
			count++;
		}
		/* send dummy ACK */
		res = send_message(&r);
		if (res < 0) {
			perror("[RECEIVER] Send ACK error. Exiting.\n");
			return -1;
		}
	}
	printf("wrong frames counter: %d\n", count);
	printf("[RECEIVER] Finished receiving..\n");
	return 0;
}
