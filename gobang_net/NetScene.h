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
	����PlayerMessage
	*/
	void setPlayerMessage(const Player_Message &message);
	/*
	����GameMessage
	*/
	void setGameMessage(const Game_Message &message);

	/*
	�������1�����2����Ϣ
	*/
	//void recvPlayerMessage();

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
	�߳���ر��� �� ����
	*/
	SDL_Thread *thread;
	bool threadQuit;//�˳��̱߳�ʶ
	void initThread();//��ʼ���߳�
	void releaseThread();//�ͷ��̱߳���
	
};



#endif // !__NETSCENE__H__
