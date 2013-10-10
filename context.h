#ifndef CONTEXT_H
#define CONTEXT_H

#include <vector>
#include <cstdint>

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

	union
	{
		uint16_t data;
		uint8_t data_raw[2];
	};

	union
	{
		uint16_t crc;
		uint8_t crc_raw[2];
	};

	// A null byte for the introduce_error function
	uint8_t null_padding;

	Packet():
		type(0),
		number(0),
		data(0),
		crc(0),
		null_padding(0)
	{}

	// Set the crc field of the message
	void addCrc16();

	// Returns true if no errors were detected
	bool checkCrc16() const;
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


#endif // CONTEXT_H