#include "../toush.h"

int
main(void){
    char msg1[] = "Please chose following task:\n";
    char msg2[] = "--------------------------\n\n";
    char msg3[] = "a).Split a file \n\n";
    char msg4[] = "b).Synthesis a file \n\n";
    char msg5[] = "c).Start server \n\n";
    char msg6[] = "d).Start client \n\n";
    char msg7[] = "--------------------------\n";
    char quit[] = "CTRL+C to quit program\n\n";
	
    printf("%s%s%s%s%s%s%s%s",msg1,msg2,msg3,msg4,msg5,msg6,msg7,quit);
    char choice[1];
    int result = 0;
    while(scanf("%s",choice) == 1){
		if(strlen(choice) == 1){
			if(choice[0] == 'a'){
				printf("Please enter file name:");
				char fileName[15];//buffer overflow attack not be considered yet
				char filePath[25];
				 
				result = scanf("%s",fileName); 
				if(result == 1){
					printf("Split file name is %s\n",fileName);
					//construct a relative file path include file name
					sprintf(filePath,"%s%s",FILE_PATH,fileName);
					splitFile(filePath);
				}
			}else if(choice[0] == 'b'){
				char fileName[15]; //buffer overflow attack not be considered yet
				printf("Please enter file name:");
				result = scanf("%s",fileName); 

				if(result == 1){
					printf("Synthesis file name is %s\n",fileName);
					//Synthesis file segments into a single file
					synthesisFile(fileName);
				}
			}else if(choice[0] == 'c'){
				//startWin32Server();
				startLinuxServer();
			}else if(choice[0] == 'd'){
				//startWin32Client();
				startLinuxClient();
			}else{
				exit(0);    
			}
			printf("%s%s%s%s%s%s%s%s",msg1,msg2,msg3,msg4,msg5,msg6,msg7,quit);
		}else{
	        break;
		}
    }
    return 0;
}

