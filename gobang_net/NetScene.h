#ifndef __NETSCENE__H__
#define __NETSCENE__H__

#include "define.h"
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


/*
�̺߳��� ��Ԫ
*/
int recvThread(void *data);


class NetScene : public Scene, Room, Connector
{
	friend int recvThread(void*data);
public:
	NetScene();
	~NetScene();

	/*
	�߼������� virtual
	*/
	void logic();

	/*
	��Ⱦ������ virtual
	*/
	void render();

	/*
	ִ����Ϸ�߼�
	*/
	virtual void frame();
private:
	/*
	����wait ���߼�
	*/
	virtual void waitState();

	/*
	����start ���߼�
	*/
	virtual void startState();

	/*
	����run ���߼�
	*/
	virtual void runState() ;

	/*
	���շ�������Ϣ
	*/
	virtual void recvData();

	/*
	�ж���Ϸ״̬
	*/
	bool checkGameState();

	/*
	����waitMessage
	*/
	void getWaitMessage(const WaitMessageStruct &message);

	/*
	�������1�����2����Ϣ
	*/
	void recvPlayerMessage();

	/*
	��ʼ��button
	*/
	void initButton();

	/*
	�ص�����
	*/
	void prepareBtnCallBack();
private:
	/*�ҵı��
	*/
	int myIndex;

	/*׼��button
	*/
	Button *prepareBtn;

	/*
	�߳���غ���
	*/
	SDL_Thread *thread;
	/*�˳���ʶ
	*/
	bool threadQuit;
	void initThread();
	void releareThread();
	
};



#endif // !__NETSCENE__H__
