// HTTP servers run HTTP over TCP connections explored briefly in the client.c/server.c
// The form of the data handled is how this differs in the main

#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>


// For additional string manipulation, we'll include the string.h headers
#include <string.h>

// HTTP Server responds to a GET request for a specific resource from a client

int main() {
  // We'll create a basic server that has a fixed response for a file "index.html"
  FILE *html_file;
  html_file = fopen("index.html", "r");
  char response_body[1024];
  fgets(response_body, sizeof(response_body), html_file);

  char http_data[2048] = "HTTP/1.1 200 OK\r\n\n"; // This line forms a rudimentary http header
  // Append the response body to the http header to form the complete response
  strcat(http_data, response_body);

  printf("Listening in for requests on port 8001...");
  // Create the server socket
  int server_sock;
  server_sock = socket(AF_INET, SOCK_STREAM, 0);

  // define the server address
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(8001);
  server_address.sin_addr.s_addr = INADDR_ANY;

  // Bind server address to socket and listen
  bind(server_sock, (struct sockaddr *) &server_address, sizeof(server_address));
  listen(server_sock, 5);

  // check for connections via an infinite loop
  int client_socket;
  while(1){
    client_socket = accept(server_sock, NULL, NULL);
    printf("Serving file to client #%d\n", client_socket);
    send(client_socket, http_data, sizeof(http_data), 0);
    // may need to pause here before closing...
    // close(client_socket);
  }

  return 0;
}
