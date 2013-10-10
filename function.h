#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include <cstddef>
#include <cstdint>

#include "context.h"

class ArqFunction {
public:
	// Respond to incoming packets
	// Return true to quit
	virtual bool poll(ArqContext *context) = 0;
};

#endif // FUNCTION_H
