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
	   
	2012-12-11:
	   Today's work list:
	   1. Check codes of previous day's work, and optimize them.
	   2. Perhaps add some new functions. :)
*/

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

