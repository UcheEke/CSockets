// Server side workflow
// Create socket -> bind() to address -> listen on that address -> accept/reject connections

// Basic includes for socket programs
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

int main(){

  char response[256] = "You have connected to the server";
  // Create the server socket in the same way as the client
  int server_sock;
  server_sock = socket(AF_INET, SOCK_STREAM, 0);

  // define the server's address
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(9002);
  server_address.sin_addr.s_addr = INADDR_ANY;

  printf("Server listening for connections on port 9002...\n");

  // bind the socket to our specified IP and port
  bind(server_sock, (struct sockaddr *) &server_address, sizeof(server_address));

  // Listen on the server
  listen(server_sock, 5); // The number is the largest number of active connections the server can handle

  // Accept a client connection
  int client_socket;
  client_socket =  accept(server_sock, NULL, NULL); // The two NULL entries are usually further details about the expected client connection

  // Send a message to the connected client
  send(client_socket, response, sizeof(response), 0);

  // Close the server socket once you are done
  close(server_sock);

  return 0;
}
