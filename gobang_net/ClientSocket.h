#pragma once
#ifndef __CLIENT__SOCKET__H__
#define __CLIENT__SOCKET__H__

#include "define.h"

#define MAX_PACKET 1024

class ClientSocket
{
public:

	void closeSocket();
	void sendData(uint8_t* data, uint16_t length, uint16_t flag);
	void initNetwork(const char* pIP, int iPort);
	bool checkSocket();
	uint8_t* recvData(uint16_t &flag, uint16_t &length);

private:
	//发生异常关闭socket
	void errorClose();

private:
	TCPsocket socket;
	SDLNet_SocketSet socket_set;
};












#endif // !__CLIENT__SOCKET__H__
