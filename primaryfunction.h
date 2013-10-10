#ifndef PRIMARYFUNCTION_H
#define PRIMARYFUNCTION_H

#include "function.h"

struct Frame
{
	uint8_t number;
	bool sent;
};

class PrimaryFunction : public ArqFunction
{
public:
	PrimaryFunction();
	virtual bool poll(ArqContext *context);

private:
	Packet generatePacket(uint8_t number) const;
	void slideWindow(uint8_t number);
	void sendWindow(ArqContext *context);

	bool _beginFlag;
	
	Frame _window[3];
};

#endif // PRIMARYFUNCTION_H 
