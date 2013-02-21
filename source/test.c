#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "md5.c"

int 
main(void){
  char * sk = "12345";
  int sizeSK = strlen(sk);
  char * sk2 = sk;
  
  printf("Size: %d , value: %c \n",sizeSK,*(sk+4+1));
  char name[5] = "Shenk";
  printf("Print test: %s\n",name);
  return 0;
}
