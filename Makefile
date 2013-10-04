all:
	g++ -std=c++0x -c arq.cpp
	g++ -std=c++0x -c secondaryfunction.cpp
	g++ -std=c++0x -c primaryfunction.cpp
	g++ -std=c++0x arq.o secondaryfunction.o primaryfunction.o introduceerror.o ccitt16.o -o arq

clean:
	rm -rf arq
