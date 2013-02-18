#ifndef STD_H
#define STD_H
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "list.h"
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

#ifndef COM_H
#define COM_H
   #include "common.h"
#endif

#define NODES_PORT 8888
#define LENGTH_OF_LISTEN_QUEUE 20

/* start nodes collection to collect IP address of
   initiated peer */
void initNodesDispatch();
