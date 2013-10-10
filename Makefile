CC=g++
CFLAGS= -std=c++0x

all:
	$(CC) $(CFLAGS) -c arq.cpp
	$(CC) $(CFLAGS) -c context.cpp
	$(CC) $(CFLAGS) -c crc16.cpp
	$(CC) $(CFLAGS) -c introduceerror.cpp
	$(CC) $(CFLAGS) -c primaryfunction.cpp
	$(CC) $(CFLAGS) -c secondaryfunction.cpp
	$(CC) $(CFLAGS) arq.o context.o crc16.o introduceerror.o primaryfunction.o secondaryfunction.o -o arq

clean:
	rm -rf *.o
	rm -rf arq
