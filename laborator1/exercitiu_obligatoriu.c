#include<stdio.h>
#include<unistd.h> 
#include<stdlib.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include<fcntl.h> 
#include <errno.h>

// programul acesta l-am realizat conform specificatiilor

int main(int argc,char *argv[]) {

    int fd = open(argv[1],O_RDONLY);

    if(fd < 0) { 
			perror("Eroare");
			exit(-1);
		} 

    char buff[1024];
    while (1) {
        int rc = read (fd, buff, sizeof(buff) - 1);
        if (rc == 0) {
            close(fd);
            break;
        }
        if (rc < 0) {
            perror("eroare la citire");
			exit(-1);
        }
        if (rc > 0) {
            write(STDOUT_FILENO, buff, rc);
        }
    }

    close(fd);

    return 0;
}


