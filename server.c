#include <stdio.h>
#include <stdlib.h>

#include <arpa/inet.h>        /* htons                     */
#include <sys/socket.h>       /* socket definitions        */
#include <sys/types.h>        /* socket types              */
#include <unistd.h>           /* unix types                */
#include <string.h>           /* memset                    */

#define PORT    3000          /* Port to listen for connections on */
#define BACKLOG 4             /* The max number of connections to keep waiting */
#define CHUNK   1024          /* How much data to read from an incoming connection */

void create_http_response(int client, char *message, int message_len);

char *response =
  "<pre>\n"
  " _   _      _ _        __        __         _     _ \n"
  "| | | | ___| | | ___   \\ \\      / /__  _ __| | __| |\n"
  "| |_| |/ _ \\ | |/ _ \\   \\ \\ /\\ / / _ \\| '__| |/ _` |\n"
  "|  _  |  __/ | | (_) |   \\ V  V / (_) | |  | | (_| |\n"
  "|_| |_|\\___|_|_|\\___/     \\_/\\_/ \\___/|_|  |_|\\__,_|\n"
  "</pre>";
int main() {

  int sockfd;                                /* Listening socket         */
  int connfd;                                /* Connecting socket        */
  struct sockaddr_in address;                /* Define server params     */

  int lenread;                               /* Number of bytes read from request */
  char recv_data[CHUNK];                     /* Chunk read from incoming request */
  int response_len = strlen(response);       /* Length of response we send to the server */

  /* Start listening for connections */
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    fprintf(stderr, "Error creating socket!\n");
    exit(EXIT_FAILURE);
  }

  /* Set parameters of serveraddr */
  memset(&address, 0, sizeof(address));
  address.sin_family        = AF_INET;
  address.sin_addr.s_addr   = INADDR_ANY;
  address.sin_port          = htons( PORT );  /* Convert port to socket byte ordering */

  /* Bind the server to listen on the PORT */
  if (bind(sockfd, (struct sockaddr *) &address, sizeof(address)) < 0) {
    fprintf(stderr, "Could not bind socket to localhost:%i!\n", PORT);
    exit(EXIT_FAILURE);
  }

  /* Listen for incoming connections */
  if (listen(sockfd, BACKLOG) < 0) {
    fprintf(stderr, "Could not listen for incoming connections!\n");
    exit(EXIT_FAILURE);
  }

  /* Run the server */
  printf("Listening on port %i....", PORT);

  while ( 1 ) {
    /* Accept a connection (from anywhere) when one becomes available */
    if ( (connfd = accept(sockfd, NULL, NULL) ) < 0 ) {
      fprintf(stderr, "Could not bind incoming connection!\n");
      continue;
    }

    /* Read values from the socket */
    lenread = read(connfd, &recv_data, sizeof(recv_data));

    /* Zero out some port of recv_data */
    *(recv_data + lenread) = 0;
    printf("%s\n\n", recv_data);

    /* Send a response */
    create_http_response(connfd, response, response_len + 1);

    if ( close(connfd) < 0 ) {
      fprintf(stderr, "Could not close connection!\n");
      exit(EXIT_FAILURE);
    }
  }
}

void create_http_response(int client, char *message, int message_len) {
  send(client, "HTTP/1.0 200 OK\n", 16, 0);
  send(client, "Content-Type: text/html\n\n", 26, 0);
  send(client, message, message_len, 0);
}
