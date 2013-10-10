#include "primaryfunction.h"
#include <cassert>

PrimaryFunction::PrimaryFunction():
	_beginFlag(true)
{
}

bool PrimaryFunction::poll(ArqContext *context)
{
	std::vector<Packet> packets = context->recvFromSecondary();
	
	if(_beginFlag)
	{
		_beginFlag = false;
		_window[0].number = 0; _window[0].sent = false;
		_window[1].number = 1; _window[1].sent = false;
		_window[2].number = 2; _window[2].sent = false;
		sendWindow(context);		

		return false;
	}
	else
	{
		for(size_t i = 0; i < packets.size(); i++)
		{
			const Packet &packet = packets[i];
			
			switch(packet.type)
			{
			case Packet::ACK_PACKET:
				slideWindow(packet.number);
				if(packet.number == 13)
					return true;
				break;

			case Packet::NAK_PACKET:
				slideWindow(packet.number);
				_window[0].sent = false;
				break;
			
			default:
				assert(false);
			}
		}

		sendWindow(context);
	}

	return false;
}

Packet PrimaryFunction::generatePacket(uint8_t number) const
{
	Packet packet;
	packet.type = Packet::DATA_PACKET;
	packet.number = number;
	packet.data_raw[0] = ('A' + 2 * number);
	packet.data_raw[1] = ('A' + 2 * number + 1);
	packet.addCrc16();
	return packet;
}

void PrimaryFunction::slideWindow(uint8_t number)
{
	uint8_t amount = number - _window[0].number;
	if(amount == 0)
		return;

	for(size_t i = 0; i < 3 - amount; i++)
	{
		_window[i] = _window[i + amount];
		number =  _window[i].number;
	}
	for(size_t i = 3 - amount; i < 3; i++)
	{
		_window[i].number = ++number;
		_window[i].sent = false;
	}
}

void PrimaryFunction::sendWindow(ArqContext *context)
{
	for(size_t i = 0; i < 3; i++)
	{
		if(_window[i].number > 12)
			break;

		if(!_window[i].sent)
		{
			context->sendToSecondary(generatePacket(_window[i].number));
		}
	}
}

