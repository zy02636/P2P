#ifndef STD_H
#define STD_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#endif

//configure header file for linux or win32
#ifdef WIN32 //define windows

	#include <winsock2.h>

#else //define linux

	#include <netinet/in.h>    // for sockaddr_in
	#include <sys/types.h>    // for socket
	#include <sys/socket.h> 
        #include <arpa/inet.h>
        #include <unistd.h>
#endif

void startServer();

#ifndef COM_H
#define COM_H

#include "common.h"

#endif

#define SERVER_PORT    1988
#define LENGTH_OF_LISTEN_QUEUE 20
#define BUFFER_SIZE 1024
#define FILE_NAME_MAX_SIZE 512


