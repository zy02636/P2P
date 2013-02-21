#include "../client.h"

/* linux client to receive file */
void
startClient(){
    //set a socket address struct, to represent client's
    //the Internet address and port
    struct sockaddr_in client_addr;
    bzero(&client_addr,sizeof(client_addr)); //clean selected heap space to zero
    client_addr.sin_family = AF_INET;       //Internet cluster
    client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");//INADDR_ANY means auto get local IP
    client_addr.sin_port = htons(0);    //0 means to let the OS assign a arbitary free port
   
    //Create a TCP based Internet socket, client_socket represents the client
    int client_socket = socket(AF_INET,SOCK_STREAM,0);
    if(client_socket < 0){
        printf("Create Socket Failed!\n");
        exit(1);
    }

    //bind the client socket with client socket address struct
    if(bind(client_socket,(struct sockaddr*)&client_addr,sizeof(client_addr))){
        printf("Client Bind Port Failed!\n"); 
        exit(1);
    }

    //set a socket address struct to represent the server
    //with Internet IP address and port number
    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    
    server_addr.sin_port = htons(CONNECT_PORT);
    socklen_t server_addr_length = sizeof(server_addr);

    //attempt to connect with server, since connect successfully
    //client_socket presents a socket connection of client and server
    if(connect(client_socket,(struct sockaddr*)&server_addr, server_addr_length) < 0){
        printf("Can Not Connect To!\n");
        exit(1);
    }else{
      printf ("%s\n","Connect to server successfully! \n");
    }

    //used to tell the store path of downloaded file
    char file_path[FILE_NAME_MAX_SIZE+1];
    bzero(file_path, FILE_NAME_MAX_SIZE+1);
    printf("Please Input File Name On Server:");
    //this used to store file name
    char file_name[30];//max length of file name , may buffer overflow ...- - let it go
    int result = scanf("%s", file_name); /* this line of code potential error */
    printf ("Receive name: %d\n",result);
    sprintf(file_path,"%s%s",CLIENT_FILE_PATH,file_name);

    //send buffer to server
    send(client_socket,file_name,BUFFER_SIZE,0);

    FILE * fp = fopen(file_path,"w");
    if(NULL == fp ){
        printf("File:\t%s Can Not Open To Write\n", file_name);
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
        
        char responseType[4];
        strncpy(responseType,buffer,4);
        //different response 
        if(strcmp(responseType,"0000") == 0){
            printf ("IP list: %s\n",buffer);
        }else if(strcmp(responseType,"0001") == 0){
            printf ("Send file: %s\n",file_name);
            int write_length = fwrite(buffer,sizeof(char),length,fp);
            if(write_length < length){
                printf("File: %s write to local disk failed\n", file_path);
                break;
            }
            bzero(buffer,BUFFER_SIZE);    
        }
        break;
    }
    printf("Recieve File:\t %s From Server Finished\n",file_name);
    fclose(fp);

    //close socket
    close(client_socket);
}
