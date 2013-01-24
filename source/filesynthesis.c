#include "../filesynthesis.h"

/*
    Splite a file into a collection of segments with defined size, MD5, file MD5
*/
void synthesisFile(char *fileName){
	printf("\nBegin synthesis...\n");
    //declare a counter
    int i = 0;
	
	//declare a file pointer
	FILE *fp;
	
	//store file name
	char segName[25];
	
	//first segment name
	sprintf(segName,"%s%d",SEG_PATH,0);
	
	//open first segment
	fp = fopen(segName,"rb");
	
	//this is just a temporary solution for store whole file bytes
	//file size is fixed. Furture solution is generating a file meta
	//file to store file information, and dynamically allocate buffer
	//to file.
	char fbuffer[1024*50];
	int fsize = 0;//temp record file size
    int segSize = 0;
	do{
		if(fp != NULL){
			fseek(fp,0,SEEK_END);

			//segment size by byte
			segSize = ftell(fp);
			fsize  += segSize;
			
			printf("Segment name: %s , %d bytes \n",segName,segSize);

			//move file pointer to beigin position
			fseek(fp,0,SEEK_SET);
	
			//allocate buff to store segment bytes information
			char *buffer = malloc(sizeof(char) * segSize);
	
	        //read segment bytes into buffer
			int result = fread(buffer,segSize,1,fp);
			printf("Synthesis file state: %d \n",result);
			//concatenate segment buffer to file buffer
			strcat(fbuffer,buffer);
			
			free(buffer);
			
			//close write file
			fclose(fp);
		}
		//construct next segment file path
		i++;
	    sprintf(segName,"%s%d",SEG_PATH,i);
	}while((fp = fopen(segName,"rb+"))!= NULL);
	
	//file name
	sprintf(segName,"%s%s",SYN_FILE_PATH,fileName);
	
	printf("File stores at: %s \n",segName);
	
	fp = fopen(segName,"wb");//potential of buffer overflow attack
	//write buffer
	printf("*****  Synthesis file size is %d  *****\n",fsize);
	
	printf("*****  File md5 is: ");
	getCharsMD5((unsigned char *)fbuffer);
	printf("\n");
	printf("\nAccomplish synthesis...\n\n");
	
	fwrite(fbuffer,fsize,1,fp);
	fclose(fp);
}
