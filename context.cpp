#include "context.h"
#include "introduceerror.h"
#include "crc16.h"

#include <iostream>

void printPacket(const Packet &packet, bool primaryToSecondary)
{
	static const char *typeNames[] =
	{
		"    ",
		"data",
		"ack ",
		"nak "
	};
	static const char *pathNames[] =
	{
		"s->p",
		"p->s"
	};

	std::cout << pathNames[primaryToSecondary] <<  ": (";
	std::cout << typeNames[packet.type] << ", #";
	std::cout << (uint32_t) packet.number << ", [";
	std::cout << packet.data_raw[0] << ", " << packet.data_raw[1] << "])";
	std::cout << std::endl;
}

void Packet::addCrc16()
{
	crc = crc16_compute(reinterpret_cast<uint8_t*>(this),
		sizeof(uint8_t) +  // Packet type
		sizeof(uint8_t) +  // Packet number
		sizeof(uint16_t)); // Data
}

bool Packet::checkCrc16() const
{
	const uint16_t crc = crc16_compute(reinterpret_cast<const uint8_t*>(this),
		sizeof(uint8_t)  + // Packet type
		sizeof(uint8_t)  + // Packet number
		sizeof(uint16_t) + // Data
		sizeof(uint16_t)); // CRC

	return crc == 0;
}

void ArqContext::sendToPrimary(const Packet &packet)
{
	printPacket(packet, false);

	if(packet.type == Packet::DATA_PACKET)
		introduce_error((char*)&packet, ber);

	primaryPackets.push_back(packet);	
}

void ArqContext::sendToSecondary(const Packet &packet)
{
	printPacket(packet, true);
	
	if(packet.type == Packet::DATA_PACKET)
		introduce_error((char*)&packet, ber);

	secondaryPackets.push_back(packet);		
}

std::vector<Packet> ArqContext::recvFromPrimary()
{
	std::vector<Packet> copy = secondaryPackets;
	secondaryPackets.clear();
	return copy;
}

std::vector<Packet> ArqContext::recvFromSecondary()
{
	std::vector<Packet> copy = primaryPackets;
	primaryPackets.clear();
	return copy;
}
