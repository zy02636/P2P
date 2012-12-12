#include "../toush.h"

int
main(void){
    printf("Please chose following task: \n********** \na).Split a file \nb).Synthesis a file \nc).exit \n**********\n");
	char choice[1];
	scanf("%s", choice);
	do{
	    if(strlen(choice) == 1){
			if(choice[0] == 'a'){
				printf("Please enter file name:");
				char fileName[15];
				char filePath[25];
				
				scanf("%s",fileName); 
				printf("Split file name is %s\n",fileName);
				
				//construct a relative file path include file name
				sprintf(filePath,"%s%s",FILE_PATH,fileName);
				
				FILE *fp;
				if((fp = fopen(filePath,"rb")) != NULL){
					//Split a file into a collection of small segments with
					//defined file size
					splitFile(fp);
					fclose(fp);
				}else{
					printf("Open file fails.");
					break;
				}
			}else if(choice[0] == 'b'){
				char fileName[15];
				printf("Please enter file name:");
				scanf("%s",fileName); 
				printf("Synthesis file name is %s\n",fileName);
				
				//Synthesis file segments into a single file
				synthesisFile(fileName);
			}else{
				break;
			}
			printf("Please chose following task: \n********** \na).Split a file \nb).Synthesis a file \nc).exit \n**********\n");
		}else{
		    break;
		}
	}while(scanf("%1s", choice));//restrict buffer length to 1
    return 0;
}

