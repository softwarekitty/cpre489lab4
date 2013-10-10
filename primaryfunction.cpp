#include "function.h"
#include "primaryfunction.h"

PrimaryFunction::PrimaryFunction()
{

	Packet packets [13];
	char[][] packetContent = {{'a','b'},{'c','d'},{'e','f'},{'g','h'},{'i','j'},{'k','l'},{'m','n'},{'o','p'},{'q','r'},{'s','t'},{'u','v'},{'w','x'},{'y','z'}};
	for(size+t i = 0; i < 13; i++)
	{
		packets[i].type = 1;//maybe Packet.PacketType_t.DATA_PACKET ?
		packets[i].number = i;
		packets[i].data_raw[0]=packetContent[i][0];
		packets[i].data_raw[1]=packetContent[i][1];
		//TODO - create crc checksum info?
	}
	//TODO - ??populate window, initialize index???

}

bool PrimaryFunction::poll(ArgContext *context)
{
	//TODO
}

