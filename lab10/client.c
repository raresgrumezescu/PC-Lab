#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"

#define HOST_IP "3.8.116.10"
#define HOST_IP2 "188.166.16.132"

int main(int argc, char *argv[]) {
    char *message;
    char *response;
    int sockfd;

	char *line = calloc(LINELEN, sizeof(char));
        
    // Ex 1.1: GET dummy from main server
	sockfd = open_connection(HOST_IP, 8080, AF_INET, SOCK_STREAM, 0);
	message = compute_get_request(HOST_IP, "/api/v1/dummy", NULL, NULL, 0);
	send_to_server(sockfd, message);
	response = receive_from_server(sockfd);
	printf("%s\n\n", response);

    // Ex 1.2: POST dummy and print response from main server
	sprintf(line, "field1=value1&field2=value2");
	message = compute_post_request(HOST_IP, "/api/v1/dummy","application/x-www-form-urlencoded", &line, 1, NULL, 0);
	send_to_server(sockfd, message);
	response = receive_from_server(sockfd);
	printf("%s\n\n", response);

    // Ex 2: Login into main server

	sprintf(line, "username=student&password=student");
	message = compute_post_request(HOST_IP, "/api/v1/auth/login","application/x-www-form-urlencoded", &line, 1, NULL, 0);
	send_to_server(sockfd, message);
	response = receive_from_server(sockfd);
	printf("%s\n\n", response);

    // Ex 3: GET weather key from main server
    char *tok;
    tok = strstr(response, "Set-Cookie");
    tok = strtok(tok, ": ");
    tok = strtok(NULL, ";");
	message = compute_get_request(HOST_IP, "/api/v1/weather/key", NULL, &tok, 1);
	send_to_server(sockfd, message);
	response = receive_from_server(sockfd);
	printf("%s\n\n", response);
	close_connection(sockfd);

    tok = strstr(response, "{\"key\"");
    tok = strtok(tok, ": {\"}");
    tok = strtok(NULL, ": {\"}");
	
    // Ex 4: GET weather data from OpenWeather API
    double buc_lat = 44.4268;
    double buc_lon = 26.1025;
	sprintf(line, "lat=%lf&lon=%lf&APPID=%s",buc_lat, buc_lon, tok);
    sockfd = open_connection(HOST_IP2, 80, AF_INET, SOCK_STREAM, 0);
	message = compute_get_request(HOST_IP2, "/data/2.5/weather", line, NULL, 0);
	send_to_server(sockfd, message);
	response = receive_from_server(sockfd);
	printf("%s\n\n", response);
	close_connection(sockfd);
    // Ex 5: POST weather data for verification to main server
    // Ex 6: Logout from main server
    sockfd = open_connection(HOST_IP, 8080, AF_INET, SOCK_STREAM, 0);
	message = compute_get_request(HOST_IP, "/api/v1/auth/logout", NULL, NULL, 0);
	send_to_server(sockfd, message);
	response = receive_from_server(sockfd);
	printf("%s\n\n", response);
	close_connection(sockfd);
    return 0;
}