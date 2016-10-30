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

	/*
	接收服务器消息
	*/
	virtual void recvData() = 0;

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
	
	/*
	从服务器接收的数据   消息类型flag，数据长度length，数据data
	*/
	FlagType flag;
	LengthType length;
	DataType data;
};


#endif // !__CONNECTOR__H__



