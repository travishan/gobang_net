#ifndef __NETSCENE__H__
#define __NETSCENE__H__

#include "define.h"
#include "Room.h"
#include "Connector.h"
#include "SceneManager.h"



/******************

NetScene�����̳���Scene��Room�࣬ͬʱ�����������������߼�����Ⱦ�Ĺ��ܣ�ͬʱ����ͷ���˽��н�����
Room����Ҫ�����˵�ǰһ����Ϸ��������غ�����ѡ����Ϊ������Ҫ�ǵ�����ս�������ս�඼���Լ̳�����࣬ʵ�ֶԲ�ͬ���ܵķ�װ��

�̳�Connector�࣬ʵ�ֺͷ��������ӵĹ���

******************/

#define SERVER_IP "127.0.0.1"
//#define SERVER_IP "115.159.220.253"
#define SERVER_PORT 9088


/*
�̺߳��� ��Ԫ
*/
int recvThreadFunc(void *data);
int sendThreadFunc(void *data);


class NetScene : public Scene, Room, Connector
{
	friend int recvThreadFunc(void*data);
	friend int sendThreadFunc(void*data);
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
	virtual void waitStateRender();

	/*
	����start ���߼�
	*/
	virtual void startState();
	virtual void startStateRender();

	/*
	����run ���߼�
	*/
	virtual void runState() ;
	virtual void runStateRender();

	/*
	����end ���߼�
	*/
	virtual void endState();
	virtual void endStateRender();
	/*
	����PlayerMessage
	*/
	void setPlayerMessage(const Player_Message &message);
	/*
	����GameMessage
	*/
	void setGameMessage(const Game_Message &message);

	/*
	��ʼ��button
	*/
	void initButton();

	/*
	�ص�����
	*/
	void prepareCallback();
	void restartCallback();

	/*
	���ݷ�������Ϣ���õ��ֵ�����
	*/
	void setAnotherPoint(B_POINT point);

private:

	/*button
	*/
	Button *prepareBtn;//׼����ť
	Button *restartBtn;//���¿�ʼ��ť

	/*
	�߳���ر��� �� ����
	*/
	SDL_Thread *thread,*sendThread;
	bool threadQuit;//�˳��̱߳�ʶ
	bool sendFlag;//���ͱ�ʶ

	void initThread();//��ʼ���߳�
	void releaseThread();//�ͷ��̱߳���

	/*
	����������ʹ�����ظ����ܽ�����Ϣ
	*/
	bool ended;

};



#endif // !__NETSCENE__H__
