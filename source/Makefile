EXEC = toush
CC = gcc
CFLAGS  = -c -Wall -O -g

$(EXEC):toush.o filesplitter.o filesynthesis.o
	$(CC) -o $(EXEC) toush.o filesplitter.o filesynthesis.o

toush.o:../filesplitter.h ../filesynthesis.h toush.c
	$(CC) $(CFLAGS) toush.c	

filesplitter.o:../filesplitter.h filesplitter.c
	$(CC) $(CFLAGS) filesplitter.c
	
filesynthesis.o:../filesynthesis.h filesynthesis.c
	$(CC) $(CFLAGS) filesynthesis.c
	
clean:
	rm -rf *.o $(EXEC)

