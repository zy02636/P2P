EXEC = toush
CC = gcc
CFLAGS  = -c -Wall -O -g

$(EXEC):toush.o filesplitter.o
	$(CC) -o $(EXEC) toush.o filesplitter.o

toush.o:../filesplitter.h toush.c
	$(CC) $(CFLAGS) toush.c	

filesplitter.o:../filesplitter.h filesplitter.c
	$(CC) $(CFLAGS) filesplitter.c
	
clean:
	rm -rf *.o $(EXEC)

