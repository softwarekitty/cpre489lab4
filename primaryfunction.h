#ifndef PRIMARYFUNCTION_H
#define PRIMARYFUNCTION_H

#include "function.h"

class PrimaryFunction : public ArqFunction
{
public:
	virtual bool poll(ArqContext *context) { return true; }

private:
	Packet window[3];

	Packet *index;
	Packet packets[13]; 
};

#endif // PRIMARYFUNCTION_H 
