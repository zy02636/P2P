Since I am have an intership in the company, and just like other intership guys have experienced that 
you will have plenty plenty plenty time during your intership. After several weeks of working, 
work load is fine and not that difficult. Therefore I have decided to find some fun by myself. Here is some 
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
   
   1.Reorganise the project seems much nicer.
   2.Split txt file and synthesis segments works fine, but in terms of jpg and docx or other forms
     of file, synthesis function does not work properly..em needs to be fixed in the following days.
	 
2012-12-12:
    Heavy snow! WOW, that is cold.
	Since I may have to test an app today, so not too much improvement will be added to this program. 
	1. Add logic control of user input to chose which function to execute(just to avoid recomplie the program)
	2. If get enough time, check where split and synthesis file does not work properly

	1. Add branch control, avoid recomplie,make the program easy to manipulate
	2. Use function: fflush(fp) to solve the weired empty segment problem
	3. Merge file segments still cannot work
	
2012-12-13:
    Thursday is kind of busy. During the lunch time I will try to figure out the issue of bytes losing when
	synthesising file segments.
	For the moment, hint is that file has two different structure: one is ASCII file and another
	is binary file structure. I have switch read/write mode to binary mode, this change solves the issue
	of segment size unalignment. However merged image still does not work well. LOL

    After sevral hours trial...damn, i have check the file before split and after synthesis.. their byte size
    is same, and their MD5 are also the same!!damn...	

2012-12-17:
    Ok, guys back to work. Since I have a quite nice weekend, watched some films and read some books, I just 
	totally forgot this little cute program. To ensure the progress of this program, i have decided to put 
	the merge file issue aside, and move on to other functions. As usual, spent lunch time to accomplish this task.
	1. Send file segments through socket.

    1.Not done LOL.. socket program in Windows written by C...damn, i just cant find proper head file.
	Even google for it does not help too much..em check it out later, i have to work la.

2012-12-18:
    Ok, continue yesterday's work. Find someone's socket exampl on git. Hope these codes may work. 
	
	Find some code that is complieable, just add -lwsock32 in the complie command..Xiuuuuu. done 
	Well, let's explore it with detail.
	
2012-12-19:
    Finally,got much more simple code to build sever/client introduction program..Ha, ok finish lunch time

2012-12-21:
    Integrate server and client, but there is weired issues:
	1. Socket only send 4 bytes data.
	2. ASCII file and binary file has not been handled proper. For the moment, it seems only
	ASCII file can be sent by the socket, check binary later.
	
2013-03-19
    You may notice that this project seems not updating for quite a long time.. But trust me, I will update soon. For the moment, I just try to figure out how to desgin a much simpler structure, but no compromise to flexibility and quanlity. The basic idea is to make two programs: node dispath center and nodes.

