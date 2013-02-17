#include "../server.h"

/*
void startWin32Server(){
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
}*/

/*
   Linux OS based socket server
*/
void startLinuxServer(){
    //设置一个socket地址结构server_addr,代表服务器internet地址, 端口
    struct sockaddr_in server_addr;
    //定义客户端的socket地址结构client_addr
    struct sockaddr_in client_addr;
    bzero(&server_addr,sizeof(server_addr)); //把一段内存区的内容全部设置为0
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);

    //创建用于internet的流协议(TCP)socket,用server_socket代表服务器socket
    int server_socket = socket(PF_INET,SOCK_STREAM,0);
    if( server_socket < 0)
    {
        printf("Create Socket Failed!");
        exit(1);
    }

   int opt =1;
   setsockopt(server_socket,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    
    //把socket和socket地址结构联系起来
    if( bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr)))
    {
        printf("Server Bind Port : %d Failed!", HELLO_WORLD_SERVER_PORT); 
        exit(1);
    }

    //server_socket用于监听
    if(listen(server_socket, LENGTH_OF_LISTEN_QUEUE))
    {
        printf("Server Listen Failed!"); 
        exit(1);
    }

    printf("accept client %s/n",inet_ntoa(client_addr.sin_addr));  
    while (1) //服务器端要一直运行
    {
        socklen_t length = sizeof(client_addr);

        //接受一个到server_socket代表的socket的一个连接
        //如果没有连接请求,就等待到有连接请求--这是accept函数的特性
        //accept函数返回一个新的socket,这个socket(new_server_socket)用于同连接到的客户的通信
        //new_server_socket代表了服务器和客户端之间的一个通信通道
        //accept函数把连接到的客户端信息填写到客户端的socket地址结构client_addr中
        int new_server_socket = accept(server_socket,(struct sockaddr*)&client_addr,&length);
        if ( new_server_socket < 0)
        {
            printf("Server Accept Failed!\n");
            break;
        }
        
        char buffer[BUFFER_SIZE];
        bzero(buffer, BUFFER_SIZE);
        length = recv(new_server_socket,buffer,BUFFER_SIZE,0);
        if (length < 0)
        {
            printf("Server Recieve Data Failed!\n");
            break;
        }
        char file_name[FILE_NAME_MAX_SIZE+1];
        bzero(file_name, FILE_NAME_MAX_SIZE+1);
	sprintf(file_name,"%s%s",SERVER_FILE_PATH,buffer);
        //strncpy(file_name, buffer, strlen(buffer));

        printf("%s\n",file_name);
        FILE * fp = fopen(file_name,"r");
        if(NULL == fp )
        {
            printf("File:\t %s Not Found\n", file_name);
        }
        else
        {
            bzero(buffer, BUFFER_SIZE);
            int file_block_length = 0;

            while( (file_block_length = fread(buffer,sizeof(char),BUFFER_SIZE,fp))>0){
                printf("file_block_length = %d\n",file_block_length);
                //发送buffer中的字符串到new_server_socket,实际是给客户端
                if(send(new_server_socket,buffer,file_block_length,0)<0)
                {
                    printf("Send File:\t%s Failed\n", file_name);
                    break;
                }
                bzero(buffer, BUFFER_SIZE);
			}
            fclose(fp);
            printf("File:\t%s Transfer Finished\n",file_name);
        }
        //关闭与客户端的连接
        close(new_server_socket);
    }
    //关闭监听用的socket
    close(server_socket);
}
