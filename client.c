// Client socket workflow
// Create socket -> Connect to a remote address -> Receive data from that remote address

// Basic includes for most C programs
#include <stdio.h>
#include <stdlib.h>

// includes for socket definitions
#include <sys/types.h>
#include <sys/socket.h>

// Structures for address information storage
#include <netinet/in.h>
// Required header file for the function close()
#include <unistd.h>

void error(char *msg){
 perror(msg);
 exit(1);
}

int main(int argc, char *argv[]) {
  // Get the user defined port number
  int port_no;
  if (argc < 2){
    // Set default port to 8001
    printf("Connecting to localhost:8001 by default...\n");
    port_no = 8001;
  } else {
    port_no = atoi(argv[1]);
  }

  // Create the socket, using an integer reference
  int client_socket;
  // socket() with constants:
  // AF_INET: (A)ddress (F)amily - IPv4 Addresses (AF_INET6 for IPv6)
  // SOCK_STREAM: using a sequenced, reliable two-way connection based byte stream
  // last parameter = 0 (indicates protocol type is default i.e. TCP)
  client_socket = socket(AF_INET, SOCK_STREAM, 0);

  // Define the remote socket as a predefined sockaddr_in struct
  struct sockaddr_in server_addr;

  // sockaddr_in have several parameters to specify for a TCP connection
  server_addr.sin_family = AF_INET;  // Explained earlier
  // The htons() function converts the port number (an integer - uint short) from host byte order to network byte order.
  server_addr.sin_port = htons(port_no);
  // the remote server address is part of a substruct in the sockaddr_in struct
  server_addr.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY == "localhost", "0.0.0.0"

  // Now we connect to the server. Note we have to cast the server_addr as a different struct, sockaddr_in
  int connection_status;
  connection_status = connect(client_socket, (struct sockaddr *) &server_addr, sizeof(server_addr));
  // connect() returns an integer. Errors are signified by a value of -1
  if (connection_status == -1){
    error("There was an error connecting to the remote server");
  }

  // receive data from server with the recv function
  char server_response[2048];
  recv(client_socket, &server_response, sizeof(server_response), 0);

  // print out the data received from the remote server
  printf("The server sent the data: %s\n", server_response);

  // Close the socket connection
  close(client_socket);

  return 0;
}
