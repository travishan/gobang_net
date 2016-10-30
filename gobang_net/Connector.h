#ifndef __CONNECTOR__H__
#define __CONNECTOR__H__

#include "ClientSocket.h"


class Connector
{
public:
	Connector();
	~Connector();

	/*
	连接服务器，参数  ip地址 端口
	*/
	void connect(const string &ip, const int port);

	/*
	断开与服务器的连接
	*/
	void disconnect();

//private:
//
//	/*
//	处理不同的消息
//	*/
//	void handleWait();
//	void handleStart();
//	void handleRun();
//	void handleChange();
//	void handleQueryRegret();
//	void handleRegret();
//	void handleFull();
protected:
	/*
	使用SDL封装的socket层连接类
	*/
	ClientSocket client;
};


#endif // !__CONNECTOR__H__



