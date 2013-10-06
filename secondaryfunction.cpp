#include "secondaryfunction.h"
#include <iostream>

SecondaryFunction::SecondaryFunction() :
	_nextPacket(0)
{
}

bool SecondaryFunction::poll(ArqContext *context)
{
	std::vector<Packet> packets = context->recvFromPrimary();
	for(size_t i = 0; i < packets.size(); i++)
	{
		if(processPacket(context, &packets[i]))
			return true;
	}

	return false;
}

bool SecondaryFunction::processPacket(ArqContext *context, const Packet *packet)
{
	if(!packet->checkCrc16() || packet->type != Packet::DATA_PACKET)
	{
		sendNak(context, _nextPacket);
		return false;
	}

	if(packet->number > _nextPacket)
	{
		sendNak(context, _nextPacket);
		return false;
	}
	else if(packet->number == _nextPacket)
	{
		std::cout << (char) packet->data_raw[0] << (char) packet->data_raw[1] << std::endl;

		sendAck(context, _nextPacket);
		_nextPacket++;

		return packet->number == 12;
	}
	else
	{
		sendAck(context, _nextPacket);
		return false;
	}
}

void SecondaryFunction::sendAck(ArqContext *context, uint8_t packetNumber)
{
	Packet packet;
	packet.type = Packet::ACK_PACKET;
	packet.number = packetNumber;
	packet.addCrc16();

	context->sendToPrimary(packet);
}

void SecondaryFunction::sendNak(ArqContext *context, uint8_t packetNumber)
{
	Packet packet;
	packet.type = Packet::NAK_PACKET;
	packet.number = packetNumber;
	packet.addCrc16();

	context->sendToPrimary(packet);
}