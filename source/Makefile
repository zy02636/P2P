EXEC = toush
CC = gcc
CFLAGS  = -c -Wall -O -g

$(EXEC):toush.o filesplitter.o filesynthesis.o hasher.o md5.o lins.o linc.o
	$(CC) -o $(EXEC) toush.o filesplitter.o filesynthesis.o hasher.o md5.o lins.o linc.o -lpthread

toush.o:../filesplitter.h ../filesynthesis.h toush.c
	$(CC) $(CFLAGS) toush.c	
	
filesplitter.o:../filesplitter.h ../hasher.h filesplitter.c
	$(CC) $(CFLAGS) filesplitter.c
	
filesynthesis.o:../filesynthesis.h ../hasher.h filesynthesis.c
	$(CC) $(CFLAGS) filesynthesis.c 

hasher.o:../hasher.h ../md5.h hasher.c
	$(CC) $(CFLAGS) hasher.c

md5.o:../md5.h md5.c
	$(CC) $(CFLAGS) md5.c
	
lins.o:../server.h lins.c
	$(CC) $(CFLAGS) lins.c 

linc.o:../client.h linc.c
	$(CC) $(CFLAGS) linc.c 
	
cleanObj:
	rm -rf *.o
cleanAll:
	rm -rf *.o $(EXEC)