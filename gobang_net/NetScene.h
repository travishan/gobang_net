#ifndef __NETSCENE__H__
#define __NETSCENE__H__

#include "define.h"
#include "WindowManager.h"
#include "SceneManager.h"
#include "Room.h"
#include "Connector.h"

/******************

NetScene�����̳���Scene��Room�࣬ͬʱ�����������������߼�����Ⱦ�Ĺ��ܣ�ͬʱ����ͷ���˽��н�����
Room����Ҫ�����˵�ǰһ����Ϸ��������غ�����ѡ����Ϊ������Ҫ�ǵ�����ս�������ս�඼���Լ̳�����࣬ʵ�ֶԲ�ͬ���ܵķ�װ��

�̳�Connector�࣬ʵ�ֺͷ��������ӵĹ���

******************/

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 9088

class NetScene : public Scene, Room, Connector
{
public:
	NetScene();
	~NetScene();

	/*
	�߼�������  virtual
	*/
	void logic();

	/*
	��Ⱦ������ virtual
	*/
	void render();

	/*
	ִ����Ϸ�߼�
	*/
	void frame();
private:
	/*
	����wait ���߼�
	*/
	void waitState();

	/*
	����start ���߼�
	*/
	void startState();

	/*
	����run ���߼�
	*/
	void runState() ;

	/*
	���շ�������Ϣ
	*/
	virtual void recvData();

	/*
	�ж���Ϸ״̬
	*/
	void checkGameState();
private:

	
};



#endif // !__NETSCENE__H__
