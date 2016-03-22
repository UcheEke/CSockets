// HTTP clients run HTTP over TCP connections explored briefly in the client.c/server.c
// The form of the data handled is how this differs in the main

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

// HTTP Client performs GET request for a specific resource on a remote server
