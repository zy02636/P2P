/*
    Since I am have an intership in the company, and just like other intership guys have experienced that 
    you will have plenty plenty plenty time during your so called 'intership'. After several weeks of working, 
    work load is fine and not that difficutl. Therefore I have decided to find some fun by myself. Here is some 
    criteria that 'the fun' should fit:
    1. It can help me improve my prorgamming skills.
    2. It should be not too easy to implement, not like a project, but more like explore work.
    3. There is already some prieces of code that I can copy and learn from.
	   Ok, that is all I can recall for the moment about the project feature. After several minutes of thinking, 
	   em... perhaps implment a P2P file share program might be interesting. 
	   Coz I have no clues about how it works, and P2P is a quite mature 
	   technology that plenty learning materials can be obtained from the 
	   Internet. So, let's doing it.


	Log 

	2012-12-10:
	   This is the day I have decided to start the work. Ha, where to start?? After several hours of 
	   online searching, P2P program identifies each file by MD5 and it will be splited into a 
	   collection of segments. Also every segment is identified by a MD5. So today's work:
	   1. MD5 generator
	   2. Splite FILE to a collection of Segments
	   3. Generate FILE MD5
	   4. Generate Segment MD5

	   1.Ok, end of the day finish MD5 generator(actually copied it from Internet does not know the author :( ).
	   2. Split the file(only test with txt file not other binary file)
	   
	   Cons: it seems weired that if the file size exceeds 1024 the char buffer cannot be cleaned, and run program in
	   shell cannot create segment file, but run it by clicking it in GUI can produce correct amount of segment files.
	   To sum up...still many problems and confusions....LOL
*/

#include <stdlib.h>
#include <stdio.h>
#include "md5.c"

#define MD5_LEN 32
#define SEG_SIZE 256

/*
  define a file structure, and each file will
  have at least one segment.
*/
typedef struct File{
    int fileId;
    char fileMD5[32];
    long byteSize;
}File;

/*
  define a segment structure.
*/
typedef struct Segment{
    int fileId;
    int segId;
    long byteSize;
    char fileMD5[32];
    char segMD5[32];
}Segment;

/*
  To obtain MD5 of a file by input memory address
  of a file,return 16 char array. Each char stores an integer
  ranges from 0-255 and can be mapped into hex-representation 
  of stored value, such as 0xa1
*/
void
getFileMD5(FILE *fp, char *dep){
	long fileSize = 0;
    fseek(fp,0L,SEEK_END);
	fileSize = ftell(fp);
    printf("File size is: %lu \n",fileSize);

    //move file point to the begin position of a file
	fseek(fp,0L,SEEK_SET);
    //allocate buff to store file bytes information
    char *encrypt = malloc(sizeof(char)*fileSize);

	//record read file state
	int rc = -1;
	//buffer, read length, read times, file pointer
    rc = fread(encrypt,fileSize,1,fp);
	
    if(rc < 0){
	    printf("Read file error.");
	}else{
	    unsigned char decrypt[16];
	    MD5_CTX md5;//MD5 structure
		MD5Init(&md5);//initialize md5
		MD5Update(&md5,encrypt,strlen(encrypt));
		MD5Final(&md5,decrypt);
		int i;
		for(i = 0; i < 16;i++){
            printf("%02x",decrypt[i]);
			*(dep+i) = decrypt[i];
		}
		
	}
	free(encrypt);
}

/*
    Splite a file into a collection of segments with defined size, MD5, file MD5
*/
void splitFile(FILE *fp){
    long fileSize = 0;
    fseek(fp,0L,SEEK_END);
	
	//file size by byte
	fileSize = ftell(fp);
	
	//calculate the number of segments
    int segSize = fileSize / SEG_SIZE;
	
	//to ensure left bytes is writen into last segment
	int left = fileSize % SEG_SIZE;
	if(left != 0) segSize++;
	
	printf("Segsize value: %d \n",segSize);
	
	//declare a FILE pointer
	FILE *segFile;
	
	//store file name
	char segName[25];
	
	//allocate buff to store file bytes information
	char *buffer = malloc(sizeof(char) * SEG_SIZE);
	
	int i = 0;
	while(i < segSize){
		//move file point to the begin position of a file
	    fseek(fp,i*SEG_SIZE,SEEK_SET);

		//write data into buffer
		fread(buffer,fileSize,1,fp);
	
		//construct a segment name
		sprintf(segName,"segment_%d",i);
	
		//open a file stream
		segFile = fopen(segName,"w");
		
		printf("Segment name: %s \n",segName);
		
		//write buffer
		fwrite(buffer,SEG_SIZE,1,segFile);
		
		printf("i value: %d \n",i);
		i++;
		
	}
	
	//close write file
	fclose(segFile);
	//free heap allocated memory
	free(buffer);
}
int
main(void){
    FILE *fp;
    if((fp = fopen("example.txt","rt")) != NULL){
	
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

