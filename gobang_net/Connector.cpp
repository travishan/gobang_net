#include "Connector.h"



Connector::Connector() {}


Connector::~Connector() {}


/*
连接服务器，参数  ip地址 端口
*/
void Connector::connect(const string &ip, const int port) {
	client.initNetwork(ip.c_str(), port);
}

/*
断开与服务器的连接
*/
void Connector::disconnect() {
	client.closeSocket();
}

///*
//接收服务器消息
//*/
//void Connector::recv() {
//	data = client.recvData(flag, length);
//
//	switch (flag) {
//	case FLAG_WAIT:
//		handleWait();
//		break;
//	case FLAG_START:
//		handleStart();
//		break;
//	case FLAG_RUN:
//	{
//
//	}break;
//	case FLAG_CHANGE:
//	{
//
//	}break;
//	case FLAG_QUERY_REGRET:
//	{
//
//	}break;
//	case FLAG_REGRETED:
//	{
//
//	}break;
//	case FLAG_FULL:
//	{
//
//	}break;
//	}
//}
//
//
//void Connector::handleWait() {
//	cout << "当前是等待状态...   数据包长度: " << length << endl;
//}
//
//void Connector::handleStart() {
//	cout << "当前是开始状态...   数据包长度: " << length;
//	if (length != 0) {
//		CHESS_COLOR color;
//		memcpy(&color, data, length);
//		delete data;
//		cout << "  当前的颜色是: " << (color ? "白方" : "黑方") << endl;
//	}
//}
//
//void Connector::handleRun() {
//
//}
//void Connector::handleChange() {
//
//}
//void Connector::handleQueryRegret() {
//
//}
//void Connector::handleRegret() {
//
//}
//void Connector::handleFull() {
//
//}