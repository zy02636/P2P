#include "../client.h"

/* windows client */

void
startClient(){
	printf("File you wanna to sent: ");
        char fileName[15]; //buffer overflow attack not be considered yet
	char filePath[25];
	
	scanf("%s", fileName);
	sprintf(filePath,"%s%s",FILE_PATH,fileName);

	if(strlen(filePath) <= 25){
		WORD wVersionRequested;
		WSADATA wsaData;
		int ret;
		SOCKET sClient; 
		struct sockaddr_in saServer; 
		//char *ptr;
		//BOOL fSuccess = TRUE;

		wVersionRequested = MAKEWORD(2, 2); 
		ret = WSAStartup(wVersionRequested, &wsaData);
		if(ret!=0){
			printf("WSAStartup() failed!\n");
			return;
		}

		if(LOBYTE(wsaData.wVersion)!=2 || HIBYTE(wsaData.wVersion)!=2){
			WSACleanup();
			printf("Invalid WinSock version!\n");
			return;
		}
	
		sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sClient == INVALID_SOCKET){
			WSACleanup();
			printf("socket() failed!\n");
			return;
		}

		saServer.sin_family = AF_INET; 
		saServer.sin_port = htons(SERVER_PORT);
		saServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	
		ret = connect(sClient, (struct sockaddr *)&saServer, sizeof(saServer));
		if (ret == SOCKET_ERROR){
			printf("connect() failed!\n");
			closesocket(sClient); 
			WSACleanup();
			return;
		}
	 
	    FILE *fp;
    	    if((fp = fopen(filePath,"rb")) != NULL){
			int fileSize = 0;
			fseek(fp,0L,SEEK_END);

			//file size by byte
			fileSize = ftell(fp);

			printf("*****  Sent file size is %d  bytes  *****\n",fileSize);
			
			//move file pointer to beigin position
			fseek(fp,0,SEEK_SET);
			
			//malloc a buffer to store file data
			char *buffer = malloc(sizeof(char) * fileSize);
			fread(buffer,fileSize,1,fp);//write into buffer,size,read time,file pointer
			fclose(fp);
			
			//int offset = 0;

			ret = send(sClient,buffer, sizeof(buffer), 0);
			free(buffer);
		}
		
		if (ret == SOCKET_ERROR) printf("send() failed!\n");
		else                     printf("client info has been sent!\n\n");

		closesocket(sClient); 
		WSACleanup();
	}
}
