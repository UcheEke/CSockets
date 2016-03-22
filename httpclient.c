// HTTP clients run HTTP over TCP connections explored briefly in the client.c/server.c
// The form of the data handled is how this differs in the main

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

// Allows for the conversion of IP addresses
#include <arpa/inet.h>
#include <unistd.h>

// HTTP Client performs GET request for a specific resource on a remote server

void error(char *msg) {
  perror(msg);
  exit(1);
}

int main(int argc, char *argv[]){

  // Get the user defined address and port for the remote server
  char *address;
  int port_no;
  if (argc < 3){
    error("Usage: httpclient <address> <port>\n");
  } else {
    address = argv[1];
    port_no = atoi(argv[2]);
  }
  int client_socket;
  client_socket = socket(AF_INET, SOCK_STREAM, 0);

  // Connect to an address
  struct sockaddr_in remote_address;
  remote_address.sin_family = AF_INET;
  remote_address.sin_port = htons(port_no);
  // Convert the user defined address from the cmdline to a usable format for the remote_address struct
  inet_aton(address, &remote_address.sin_addr.s_addr);
  connect(client_socket, (struct sockaddr *) &remote_address, sizeof(remote_address));

  char request[] = "GET / HTTP/1.1\r\n\r\n"; // Create a GET request
  char response[4096];

  // Send the request
  send(client_socket, request, sizeof(request), 0);
  // Receive the response
  recv(client_socket, &response, sizeof(response), 0);

  printf("Server response:\n\n%s\n",response);
  close(client_socket);
  return 0;
}
