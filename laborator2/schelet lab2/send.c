#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "link_emulator/lib.h"

#define HOST "127.0.0.1"
#define PORT 10000

/*
int main(int argc,char** argv){
  init(HOST,PORT);
  msg t;

  //Send dummy message:
  printf("[send] Sending dummy...\n");
  sprintf(t.payload,"%s", "This is a dummy.");
  t.len = strlen(t.payload)+1;
  send_message(&t);
  
  // Check response:
  if (recv_message(&t)<0){
    perror("Receive error ...");
    return -1;
  }
  else {
    printf("[send] Got reply with payload: %s\n", t.payload);
  }

  return 0;
}
*/

int main(int argc,char** argv){
  init(HOST,PORT);
  msg t;

  //Send dummy message:
  printf("[send] Sending dummy...\n");
  sprintf(t.payload, "%s", "fisier");

  t.len = strlen(t.payload)+1;

  send_message(&t);
  
  // Check response:
  if (recv_message(&t)<0){
    perror("Receive error ...");
    return -1;
  }
  else {
    printf("[send] Got reply with payload: %s\n", t.payload);
  }

	int fd;
  int citire;

	fd = open("fisier", O_RDONLY);
  	
  if (fd < 0) {
  	perror("eroare la deschidere send");
  	exit(-1);
  }

  char buff[1024];
	while (1) {

		//citire = read(fd, t.payload, sizeof(t.payload) - 1);
    citire = read (fd, buff, sizeof(buff) - 1);

  		if (citire < 0) {
  			close(fd);
  			perror("eroare la citire");
  			exit(-1);
  		} 
    		else {
  			t.len = citire;
  		}

    	if (citire == 0){
  			close(fd);
  			exit(-1);
  		}

  		send_message(&t);

  		if (recv_message(&t) < 0) {
    		perror("Receive error ...");
    		return -1;
  		}
  
   		else {  		
      			printf("[send] Got reply with payload: %s\n", t.payload);
    		}
	}

  return 0;
}