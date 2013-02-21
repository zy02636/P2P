#include "../server.h"

/* windows socket program */

void 
startServer(){
    WORD wVersionRequested;
    WSADATA wsaData;
    int ret, nLeft, length;
    SOCKET sListen, sServer; 

    struct sockaddr_in saServer, saClient;  
    char *ptr; 
  
    wVersionRequested = MAKEWORD(2,2); 
    ret = WSAStartup(wVersionRequested, &wsaData);
    if(ret != 0){
        printf("WSAStartup() failed!\n");
        return;
    }
  
    sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sListen == INVALID_SOCKET){
        WSACleanup();
        printf("socket() faild!\n");
        return;
    }

    saServer.sin_family = AF_INET; 
    saServer.sin_port = htons(SERVER_PORT);
    saServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
  

    ret = bind(sListen, (struct sockaddr *)&saServer, sizeof(saServer));
    if (ret == SOCKET_ERROR){
        printf("bind() faild! code:%d\n", WSAGetLastError());
        closesocket(sListen); 
        WSACleanup();
        return;
    }
  

    ret = listen(sListen, 5);
    if (ret == SOCKET_ERROR){
        printf("listen() faild! code:%d\n", WSAGetLastError());
        closesocket(sListen);
        return;
    }
  
    printf("Waiting for client connecting!\n");
    printf("Tips: Ctrl+c to quit!\n");

    while(1){ 
		length = sizeof(saClient);
		sServer = accept(sListen, (struct sockaddr *)&saClient, &length);
		if (sServer == INVALID_SOCKET){
			printf("accept() faild! code:%d\n", WSAGetLastError());
			closesocket(sListen);
			WSACleanup();
			return;
		}       
		char receiveMessage[5*1024];
		nLeft = sizeof(receiveMessage);
		ptr = (char *)&receiveMessage;
	
		while(nLeft>0){

			ret = recv(sServer, ptr, 5000, 0);
			if (ret == SOCKET_ERROR){
				printf("recv() failed!\n");
				return;
			}
			if (ret == 0){ 
				printf("Client has closed the connection\n");
				break;
			}
			nLeft -= ret;
			ptr += ret;
		}  
		printf("receive message:%s\n", receiveMessage);
 
	} 
}
