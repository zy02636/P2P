#ifndef STD_H
#define STD_H

	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>

#endif

#ifdef WIN32

    #include <winsock2.h>

#else
    
	#include <netinet/in.h>    // for sockaddr_in
	#include <sys/types.h>    // for socket
	#include <sys/socket.h>
        #include <arpa/inet.h>
	#include <unistd.h>
        
#endif

void startClient();

#ifndef COM_H
#define COM_H

   #include "common.h"

#endif

#define CONNECT_PORT    8888
#define BUFFER_SIZE 1024
#define FILE_NAME_MAX_SIZE 512
