#include <string>
#include <iostream>
#include <cstdio>
#include "primaryfunction.h"
#include "secondaryfunction.h"

int main(int argc, char **argv) 
{
	double ber;

	if(argc < 2)
	{
		std::cout << "arq <ber>" << std::endl;
		return -1;
	}
	else
	{
		sscanf(argv[1], "%d", &ber);
	}

	ArqContext context(ber);
	PrimaryFunction primary;
	SecondaryFunction secondary;

	bool primaryDone = false;
	bool secondaryDone = false;
	while(!primaryDone && !secondaryDone)
	{
		if(!primaryDone)
			primaryDone = primary.poll(&context);
		if(!secondaryDone)
			secondaryDone = secondary.poll(&context);
	}

	return 0;
}
