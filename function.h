#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include <cstddef>
#include <cstdint>
#include "introduceerror.h"

struct Packet
{
	enum PacketType_t
	{
		DATA_PACKET = 1,
		ACK_PACKET  = 2,
		NAK_PACKET  = 3
	};

	uint8_t type;
	uint8_t number;
	uint8_t data[2];

	union
	{
		uint16_t crc;
		uint8_t crc_raw[2];
	};

	uint8_t null_padding;

	Packet():
		type(DATA_PACKET),
		number(0),
		crc(0),
		null_padding(0)
	{}
};

class ArqContext {
public:
	ArqContext(double ber): ber(ber) {}

	void sendToPrimary(const Packet &packet);
	void sendToSecondary(const Packet &packet);

	std::vector<Packet> recvFromPrimary();
	std::vector<Packet> recvFromSecondary();

private:
	double ber;
	std::vector<Packet> primaryPackets;
	std::vector<Packet> secondaryPackets;
};

class ArqFunction {
public:
	// Respond to incoming packets
	// Return true to quit
	virtual bool poll(ArqContext *context) = 0;
};

#endif // FUNCTION_H
