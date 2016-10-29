#include "ClientSocket.h"






void ClientSocket::closeSocket() {
	if (SDLNet_TCP_DelSocket(socket_set, socket) == -1) {
		fprintf(stderr, "%s\n", SDLNet_GetError());
		system("pause");
		exit(-1);
	}

	SDLNet_FreeSocketSet(socket_set);
	SDLNet_TCP_Close(socket);
}

void ClientSocket::sendData(uint8_t* data, uint16_t length, uint16_t flag) {

	uint8_t tempData[MAX_PACKET];

	int offset = 0;
	memcpy(tempData + offset, &flag, sizeof(uint16_t));
	offset += sizeof(uint16_t);

	memcpy(tempData + offset, &length, sizeof(uint16_t));
	offset += sizeof(uint16_t);

	memcpy(tempData + offset, data, length);
	offset += length;

	int num_sent = SDLNet_TCP_Send(socket, tempData, offset);
	if (num_sent < length) {
		fprintf(stderr, "ER: SDLNet_TCP_Send: %s\n", SDLNet_GetError());
		closeSocket();
	}
}


uint8_t* ClientSocket::recvData(uint16_t &flag,uint16_t &length) {
	int numRecv = SDLNet_TCP_Recv(socket, &flag, sizeof(uint16_t));
	if (numRecv <= 0) {//若numRecv小于0  则发生异常 关闭socket
		errorClose();
		return nullptr;
	} else {//否则，接收剩余消息的长度信息
		numRecv = SDLNet_TCP_Recv(socket, &length, sizeof(uint16_t));
		if (numRecv <= 0) {//若numRecv小于0  则发生异常 关闭socket
			errorClose();
			return nullptr;
		} else if (length > 0) {//若length大于0 ，则接收剩余信息
			uint8_t *tempData = new uint8_t[length];
			numRecv = SDLNet_TCP_Recv(socket, tempData, length);
			if (numRecv <= 0) {//若numRecv小于0  则发生异常 关闭socket
				errorClose();
				return nullptr;
			} else {
				return tempData;
			}
		} else {
			return nullptr;
		}
	}
}


void ClientSocket::initNetwork(const char* pIP, int iPort) {
	IPaddress ip;
	if (SDLNet_ResolveHost(&ip, pIP, iPort) == -1) {
		fprintf(stderr, "%s\n", SDLNet_GetError());
		system("pause");
		exit(-1);
	}

	socket = SDLNet_TCP_Open(&ip);
	if (socket == NULL) {
		fprintf(stderr, "%s\n", SDLNet_GetError());
		cerr << SDLNet_GetError() << endl;
		system("pause");
		exit(-1);
	}

	socket_set = SDLNet_AllocSocketSet(1);
	if (socket_set == NULL) {
		fprintf(stderr, "%s\n", SDLNet_GetError());
		system("pause");
		exit(-1);
	}

	if (SDLNet_TCP_AddSocket(socket_set, socket) == -1) {
		fprintf(stderr, "%s\n", SDLNet_GetError());
		system("pause");
		exit(-1);
	}
}


bool ClientSocket::checkSocket() {
	if (SDLNet_CheckSockets(socket_set, 0) == -1) {
		fprintf(stderr, "%s\n", SDLNet_GetError());
		system("pause");
		exit(-1);
	}

	return SDLNet_SocketReady(socket);
}



void ClientSocket::errorClose() {
	closeSocket();

	const char* err = SDLNet_GetError();
	if (strlen(err) == 0) {
		printf("DB: server shutdown\n");
	} else {
		fprintf(stderr, "ER: SDLNet_TCP_Recv: %s\n", err);
	}
}


