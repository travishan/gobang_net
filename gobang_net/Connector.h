#ifndef __CONNECTOR__H__
#define __CONNECTOR__H__

#include "ClientSocket.h"


class Connector
{
public:
	Connector();
	~Connector();

	/*
	���ӷ�����������  ip��ַ �˿�
	*/
	void connect(const string &ip, const int port);

	/*
	�Ͽ��������������
	*/
	void disconnect();

//private:
//
//	/*
//	����ͬ����Ϣ
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
	ʹ��SDL��װ��socket��������
	*/
	ClientSocket client;
};


#endif // !__CONNECTOR__H__



