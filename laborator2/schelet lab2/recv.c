#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "link_emulator/lib.h"

#define HOST "127.0.0.1"
#define PORT 10001


int main(int argc,char** argv){
  msg r;
  init(HOST,PORT);

  if (recv_message(&r)<0){
    perror("Receive message");
    return -1;
  }

  printf("%s is received...\n", r.payload);

  sprintf(r.payload,"%s", "ACK");
  r.len = strlen(r.payload) + 1;
  send_message(&r);
  printf("[recv] ACK sent\n");

  char name[1024];
  
  strcpy(name, r.payload);
  strcat(name, ".bkt");

  int fd = open(name, O_RDONLY);
  int scriere;

  if (fd < 0) {
    perror("eroare deschidere recv");
    exit(-1);
  }

  while(1) {

    if (recv_message(&r) < 0) {
      perror("Receive message");
      return -1;
    }

    scriere = write(fd, r.payload, sizeof(r.payload));

    if (scriere < 0) {
      perror("eroare la scriere");
      exit(-1);
    }

    if (scriere == 0) {
      close(fd);
      exit(0);
    }

    printf("[recv] Got msg with payload: <%s>, sending ACK...\n", r.payload);

    sprintf(r.payload,"%s", "ACK");
    r.len = strlen(r.payload) + 1;
    send_message(&r);
    printf("[recv] ACK sent\n");
  }

  return 0;
}
