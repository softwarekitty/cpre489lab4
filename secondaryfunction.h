#ifndef SECONDARYFUNCTION_H
#define SECONDARYFUNCTION_H

#include "function.h"

class SecondaryFunction : public ArqFunction
{
public:
	virtual bool poll(ArqContext *context) { return true; }
};

#endif // SECONDARYFUNCTION_H
