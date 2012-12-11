#include "../toush.h"

int
main(void){
    FILE *fp;
    if((fp = fopen("../res/example.docx","rb")) != NULL){
	    //Split a file into a collection of small segments with
		//defined file size
		//splitFile(fp);
		
		//Synthesis file segments into a single file
		synthesisFile();
		
		fclose(fp);
    }else{
	    printf("Open file fails.");
	    return -1;
	}
    return 0;
}

