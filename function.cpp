#include "function.h"
#include "introduceerror.h"

void ArqContext::sendToPrimary(const Packet &packet)
{
	if(packet.type == Packet.DATA_PACKET)
		IntroduceError((char*)&packet, ber);

	primaryPackets.push_back(packet);	
}

void ArqContext::sendToSecondary(const Packet &packet)
{
	if(packet.type == Packet.DATA_PACKET)
		IntroduceError((char*)&packet, ber);

	secondaryPackets.push_back(packet);		
}

std::vector<Packet> recvFromPrimary()
{
	std::vector<Packet> copy = secondaryPackets;
	secondaryPackets.clear();
	return copy;
}

std::vector<Packet> recvFromSecondary()
{
	std::vector<Packet> copy = primaryPackets;
	primaryPackets.clear();
	return copy;
}
