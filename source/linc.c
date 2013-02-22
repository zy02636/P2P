#include "../client.h"

/*
  name:write_data
  func:receive data from other nodes and write to file
  para:pass_arg
  resu:void
*/
void* rece_data(void *ptr){
      int client_socket;
      pass_arg *param = (pass_arg *)ptr;
      client_socket = *((int *)param->fd);
      char *file_name = (char *)param->buffer;

      printf ("Client to server: %d\n",client_socket);
      printf ("Client to server name:%s\n",file_name);

      //construct the path of target file
      char file_path[FILE_NAME_MAX_SIZE+1];
      bzero(file_path, FILE_NAME_MAX_SIZE+1);
      sprintf(file_path,"%s%s",CLIENT_FILE_PATH,file_name);

      //send buffer to server
      send(client_socket, file_name, BUFFER_SIZE, 0);

      FILE * fp = fopen(file_path,"w");
      if(NULL == fp ){
            printf("File:\t%s Can not open to write\n", file_name);
            exit(1);
      }

      //store buffer from server
      char buffer[BUFFER_SIZE];
      bzero(buffer,BUFFER_SIZE);    

      //receive data from server and store it in buffer, the 
      //third parameter
      int length = 0;
      while((length = recv(client_socket,buffer,BUFFER_SIZE,0)) > 0){
            if(length < 0){
                  printf("Recieve data from server failed! \n");
                  break;
            }
            
            //printf ("Receive buffer: %s\n",buffer);
            char responseType[4];
            strlcpy(responseType,buffer,5);
            //responseType[sizeof(responseType)-1] = '/0';
            printf ("Response type: %s,length %d\n",responseType,length);
            //different response 
            if(strcmp(responseType,"0000") == 0){
                  printf ("IP list: %s\n",buffer);
            }else if(strcmp(responseType,"0001") == 0){
                  printf("Saving  %s to local successfully!\n",file_name);
                  int write_length = fwrite(buffer + 4,sizeof(char),length,fp);
                  if(write_length < length){
                        printf("File: %s write to local disk failed\n", file_path);
                        break;
                  }
                  fclose(fp);
                  //bzero(buffer,BUFFER_SIZE);    
            }
      }
      close(client_socket);
      pthread_exit(NULL);
}

/* linux client to receive file */
void
startClient(){
      //set a socket address struct, to represent client's
      //the Internet address and port
      struct sockaddr_in client_addr;
      bzero(&client_addr,sizeof(client_addr)); //clean selected heap space to zero
      client_addr.sin_family = AF_INET;       //Internet cluster
      client_addr.sin_addr.s_addr = inet_addr(SERVER_IP);//INADDR_ANY means auto get local IP
      client_addr.sin_port = htons(0);    //0 means to let the OS assign a arbitary free port
   
      //Create a TCP based Internet socket, client_socket represents the client
      int client_socket[1];
      client_socket[0] = socket(AF_INET,SOCK_STREAM,0);
      if(client_socket[0] < 0){
            printf("Create socket failed!\n");
            exit(1);
      }

      //bind the client socket with client socket address struct
      if(bind(client_socket[0],(struct sockaddr*)&client_addr,sizeof(client_addr))){
            printf("Client bind port failed!\n"); 
            exit(1);
      }

      //set a socket address struct to represent the server
      //with Internet IP address and port number
      struct sockaddr_in server_addr;
      bzero(&server_addr,sizeof(server_addr));
      server_addr.sin_family = AF_INET;
      server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);/*!!-- replace by a nodes IP list --*/
      server_addr.sin_port = htons(SERVER_PORT);
      socklen_t server_addr_length = sizeof(server_addr);


      //attempt to connect with server, since connect successfully
      //client_socket presents a socket connection of client and server
      if(connect(client_socket[0],(struct sockaddr*)&server_addr, server_addr_length) < 0){
            printf("Can not connect to!\n");
            exit(1);
      }else{
            printf ("Connect to server %s:%d successfully! \n",SERVER_IP,SERVER_PORT);
      }
    
      printf("Please input file name on server:");
      //this used to store file name
      char file_name[30];//max length of file name , may buffer overflow ...- - let it go
      bzero(file_name,30);
      int result = scanf("%s", file_name); /* this line of code potential error */
      printf ("Receive name state: %d, value:%s\n",result,file_name);
      //for the moment only one node connects
      printf ("Client: %d\n",client_socket[0]);
      pthread_t thread;
      if(pthread_create(&thread, NULL, rece_data, &(pass_arg){client_socket,file_name}) != 0){
            printf ("%s\n","pthread_create fails. \n");
      }
      pthread_join(thread,NULL);
}
