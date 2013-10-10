#include "introduceerror.h"

#include <cstdlib>

long M = 2147483647;

void introduce_error(char *data, double p)
{
	char c, *pointer = data;
	int i;
	while (*pointer != '\0') {
		c = 0x01;
		for ( i = 0; i < 8; i++) {
			if ((double)rand()/M <= p)
				*pointer ^= c;
			c <<= 1;
		}
		pointer++;
	}
}