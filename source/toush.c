#include "../toush.h"

int
main(void){
    FILE *fp;
    if((fp = fopen("../res/example.txt","rt")) != NULL){
	
	    /*
			//buffer to store decrypt result
			unsigned char *decrypt = malloc(sizeof(unsigned char)*16);
			getFileMD5(fp,decrypt);
			printf("\nDecrypt: %x",*(decrypt+1));
			fclose(fp);
			free(decrypt);
		*/
		
		splitFile(fp);
		fclose(fp);
    }else{
	    printf("Open file fails.");
	    return -1;
	}
    return 0;
}

