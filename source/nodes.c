#include "../nodes.h"

/* When a node actived, it will send its own IP address to node
   dispatch center. Then the center reponses with a list of active 
   nodes with coresponding IP address */
void
initNodesDispatch(){
  //create head node which is the IP address of dispatch center
  list_node* head = list_create("127.0.0.1:8888");

  //set the node center address
  struct sockaddr_in nodes_addr;
  struct sockaddr_in node_addr;
  bzero(&nodes_addr,sizeof(nodes_addr));
  
  nodes_addr.sin_family = AF_INET;
  nodes_addr.sin_addr.s_addr = htons(INADDR_ANY);
  nodes_addr.sin_port = htons(NODES_PORT);

  //create protocol for internet communication for socket
  int nodes_socket = socket(PF_INET,SOCK_STREAM,0);
  if(nodes_socket < 0){
    printf ("%s\n","Create nodes dispatch center failed");
    exit(1);
  }
  int opt = 1;
  setsockopt(nodes_socket,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

  //set socket address option to avoid bind error
  int portUse = 1;
  if((setsockopt(nodes_socket,SOL_SOCKET,SO_REUSEADDR,&portUse,sizeof(portUse))) < 0){
      printf ("%s\n","setsockopt failed");
      exit(1);
  }

  //connect socket with socket address
  int bindRresult = bind(nodes_socket,(struct sockaddr*)&nodes_addr,sizeof(nodes_addr));
  printf ("%s%d\n","Bind result",bindRresult);
  if(bind(nodes_socket,(struct sockaddr*)&nodes_addr,sizeof(nodes_addr)) > 0){
    printf("Node dispatch center bind port : %d failed!", NODES_PORT); /*  */
    exit(1);
  }

  //server_socket for listing port
  if(listen(nodes_socket, LENGTH_OF_LISTEN_QUEUE)){
    printf("Node dispatch center listen failed!"); 
    exit(1);
  }

  printf("accept, nodes dispatch center at IP: %s:%d \n",inet_ntoa(nodes_addr.sin_addr),NODES_PORT);  
  while(1){
    socklen_t length = sizeof(node_addr);
    int new_node_socket = accept(nodes_socket,(struct sockaddr*)&node_addr,&length);
    if(new_node_socket < 0){
      printf ("%s\n","Nodes dispatch center failed!\n");
      break;
    }

    char *buffer;
    buffer = malloc(sizeof(char) * 30);
    sprintf(buffer,"%s:%d",inet_ntoa(node_addr.sin_addr),ntohs(node_addr.sin_port));
    printf ("One node added,address: %s\n",buffer);
    
    //write connected client address into linkedlist
    list_insert_end(head,buffer);
    list_node* temp;
    temp = head;
    while(head->next != NULL){
      printf ("%s\n",(char *)head->data);
      head = head->next;
    }
    head = temp;
  }
}

int 
main(void){
  initNodesDispatch(); 
}
