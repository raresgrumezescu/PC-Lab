#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "lib.h"

#define HOST "127.0.0.1"
#define PORT 10000

char sum(msg r) {
	char ans = 0;
	for(int i = 0; i < r.len - 1; i++) {
		ans ^= r.payload[i];
	}
	return ans;
}


int main(int argc, char *argv[])
{
	msg t;
	memset(&t, 0, sizeof(msg));
	int res;
	int winSize = (atoi(argv[1]) * 1000) / (MSGSIZE * 8);
	printf("[SENDER] Starting.\n");	
	init(HOST, PORT);
	for(int i = 0; i < winSize; i++) {
		t.len = MSGSIZE;
		t.payload[MSGSIZE - 1] = sum(t);
		res = send_message(&t);
		if (res < 0) {
			perror("[SENDER] Send error. Exiting.\n");
			return -1;
		}
	}
	// printf("[SENDER]: BDP=%d\n", atoi(argv[1]));
	
	for (int i = 0; i < COUNT - winSize; i++) {
		/* cleanup msg */
		memset(&t, 0, sizeof(msg));
		t.len = MSGSIZE;
		t.payload[MSGSIZE - 1] = sum(t);
		/* send msg */
		res = send_message(&t);
		if (res < 0) {
			perror("[SENDER] Send error. Exiting.\n");
			return -1;
		}
		
		/* wait for ACK */
		res = recv_message(&t);
		if (res < 0) {
			perror("[SENDER] Receive error. Exiting.\n");
			return -1;
		}
	}

	for(int i = 0; i < winSize; i++) {
		res = recv_message(&t);
		if (res < 0) {
			perror("[SENDER] Receive error. Exiting.\n");
			return -1;
		}
	}
	printf("[SENDER] Job done, all sent.\n");
		
	return 0;
}
