#ifndef STD_H
#define STD_H

	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>

#endif

#ifdef WIN32

    #include <winsock2.h>

    void startWin32Client();

#else
    
	#include <netinet/in.h>    // for sockaddr_in
	#include <sys/types.h>    // for socket
	#include <sys/socket.h>
        #include <arpa/inet.h>
	#include <unistd.h>
        void startLinuxClient();
        
#endif

#ifndef COM_H
#define COM_H

   #include "common.h"

#endif

#define HELLO_WORLD_SERVER_PORT    6666
#define BUFFER_SIZE 1024
#define FILE_NAME_MAX_SIZE 512


