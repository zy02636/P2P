#include "../server.h"

/*
  name: send_data
  func: send data to connected client
  para: pass_arg					
  resu: void
*/
void* send_data(void *ptr){
      int client_socketfd;
      char buffer_send[BUFFER_SIZE];
      pass_arg *param = (pass_arg *)ptr;
      client_socketfd = *((int *)param->fd);
      char * file_name = (char *)param->buffer;

      char file_path[FILE_NAME_MAX_SIZE+1];
      bzero(file_path, FILE_NAME_MAX_SIZE+1);
      sprintf(file_path,"%s%s",SERVER_FILE_PATH,file_name);
   
      printf("Send file in path: %s\n",file_path);
      FILE * fp = fopen(file_path,"r");
      if(NULL == fp ){
            printf("File:\t %s not found.\n", file_path);
      } else {
            bzero(file_name, BUFFER_SIZE);
            int file_block_length = 0;
            
            //strcat(buffer_send,RESPONSE_FILE);//set repsone type
            while((file_block_length = fread(buffer_send,sizeof(char),BUFFER_SIZE,fp))>0){
                  //printf("file_block_length = %d\n, content: %s",file_block_length,buffer_send);
                  //set buffer through new_server_socket channel to client
                  char final_buffer[BUFFER_SIZE];
                  sprintf(final_buffer,"%s%s","0001",buffer_send);//set reponse type
                  //printf ("client_socketfd: %d\n",client_socketfd);
                  if(send(client_socketfd,final_buffer,file_block_length + 4,0) < 0){
                        printf("Send file:\t%s failed\n", file_path);
                        break;
                  }
                  bzero(buffer_send, BUFFER_SIZE);
            }
            fclose(fp);
            printf("File:\t%s transfer finished.\n",file_path);
      }
      //close connection with client

      close(client_socketfd);
      pthread_exit(NULL);
}

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
      int server_socket = socket(AF_INET,SOCK_STREAM,0);
      if(server_socket < 0){
            printf("Create socket failed!");
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
            printf("Server bind port : %d failed!", SERVER_PORT); 
            exit(1);
      }
      //listening on server_socket
      if(listen(server_socket, LENGTH_OF_LISTEN_QUEUE)){
            printf("Server listen failed!"); 
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
            int new_client_socket[1];
            new_client_socket[0] = accept(server_socket,(struct sockaddr*)&client_addr,&length);
            printf ("new_client_socket: %d\n",*new_client_socket);
            if (*new_client_socket < 0){
                  printf("Server accept failed!\n");
                  continue;
            }
        
            //target send file name
            char buffer[BUFFER_SIZE];
            bzero(buffer, BUFFER_SIZE);
            length = recv(*new_client_socket,buffer,BUFFER_SIZE,0);
            if (length < 0){
                  printf("Server recieve data failed!\n");
                  break;
            }

            //create different sub thread to response to different client
            pthread_t thread; 
            if(pthread_create(&thread, NULL, send_data, &(pass_arg){new_client_socket,buffer}) != 0){
                  printf ("%s\n","pthread_create fails.\n");
                  break;
            }
            pthread_join(thread,NULL);
      }
      //shutdown(new_client_socket[0],2);
      //close server listening socket and client sending socket
      shutdown(server_socket,2);
}

