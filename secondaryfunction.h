#ifndef SECONDARYFUNCTION_H
#define SECONDARYFUNCTION_H

#include "function.h"

class SecondaryFunction : public ArqFunction
{
public:
	SecondaryFunction();
	virtual bool poll(ArqContext *context);

private:
	bool processPacket(ArqContext *context, const Packet *packet);
	void sendAck(ArqContext *context, uint8_t packetNumber);
	void sendNak(ArqContext *context, uint8_t packetNumber);
	
	uint8_t _nextPacket;
};

#endif // SECONDARYFUNCTION_H
