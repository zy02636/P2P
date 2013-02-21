#include "../server.h"

/*
   Linux OS based socket server
*/
void 
startServer(){
    //add a socket address struct for server, server_addr
    //to store IP address and port number
    struct sockaddr_in server_addr;

    //define client socket address struct
    struct sockaddr_in client_addr;
    bzero(&server_addr,sizeof(server_addr)); //
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);

    //define TCP socket bases on Internet
    //server_socket represents the server socket
    int server_socket = socket(PF_INET,SOCK_STREAM,0);
    if(server_socket < 0){
        printf("Create Socket Failed!");
        exit(1);
    }

    int opt = 1;
    setsockopt(server_socket,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    //set socket address option to avoid bind error
    int portUse = 1;
    if((setsockopt(server_socket,SOL_SOCKET,SO_REUSEADDR,&portUse,sizeof(portUse))) < 0){
        printf ("%s\n","setsockopt failed");
        exit(1);
    }

    //bind socket with socket address struct
    int bindRresult = bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr));
    printf ("%s%d\n","Bind result",bindRresult);
    if(bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr)) > 0){
        printf("Server Bind Port : %d Failed!", SERVER_PORT); 
        exit(1);
    }

    //listening on server_socket
    if(listen(server_socket, LENGTH_OF_LISTEN_QUEUE)){
        printf("Server Listen Failed!"); 
        exit(1);
    }

    printf("accept client, node at IP: %s:%d \n",inet_ntoa(client_addr.sin_addr),SERVER_PORT);  
    //server side keep running
    while(1){
        socklen_t length = sizeof(client_addr);
     
        //a socket with a server_socket is a connection
        //if no connect request, then accpet function will wait unitl client connects
        //accept function returns a new socket and can be used to communicate with client
        //new_server_socket is a new channel between the server and a client
        //accept function fill in connection information in the socket address struct of client
        int new_server_socket = accept(server_socket,(struct sockaddr*)&client_addr,&length);
        if (new_server_socket < 0){
            printf("Server Accept Failed!\n");
            break;
        }
        
        char buffer[BUFFER_SIZE];
        bzero(buffer, BUFFER_SIZE);
        length = recv(new_server_socket,buffer,BUFFER_SIZE,0);
        if (length < 0){
            printf("Server Recieve Data Failed!\n");
            break;
        }
        char file_name[FILE_NAME_MAX_SIZE+1];
        bzero(file_name, FILE_NAME_MAX_SIZE+1);
        sprintf(file_name,"%s%s",SERVER_FILE_PATH,buffer);
        //strncpy(file_name, buffer, strlen(buffer));

        printf("%s\n",file_name);
        FILE * fp = fopen(file_name,"r");
        if(NULL == fp ){
            printf("File:\t %s Not Found\n", file_name);
        } else {
            bzero(buffer, BUFFER_SIZE);
            int file_block_length = 0;

            while((file_block_length = fread(buffer,sizeof(char),BUFFER_SIZE,fp))>0){
                printf("file_block_length = %d\n",file_block_length);
                //set buffer through new_server_socket channel to client
                if(send(new_server_socket,buffer,file_block_length,0)<0){
                  printf("Send File:\t%s Failed\n", file_name);
                  break;
                }
                bzero(buffer, BUFFER_SIZE);
            }
            fclose(fp);
            printf("File:\t%s Transfer Finished\n",file_name);
      }
      //close connection with client
      close(new_server_socket);
    }
    //close server listening socket
    close(server_socket);
}
