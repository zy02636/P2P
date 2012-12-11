#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "md5.c"

int 
main(void){
    MD5_CTX md5;
    MD5Init(&md5);
    int i;
    unsigned char encrypt[] = "admin";
    unsigned char decrypt[16];
    MD5Update(&md5,encrypt,strlen((char*)encrypt));
    MD5Final(&md5,decrypt);
    printf("Before:%s \n After: ",encrypt);
    for(i = 0; i < 16;i++){
        printf("%02x",decrypt[i]);
    }
    return 0;
}
