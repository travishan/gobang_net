#ifndef __NETSCENE__H__
#define __NETSCENE__H__

#include "define.h"
#include "SceneManager.h"
#include "Room.h"
#include "Connector.h"

/******************

NetScene场景继承了Scene和Room类，同时负担了五子棋下棋逻辑和渲染的功能，同时负责和服务端进行交互。
Room类主要保存了当前一场游戏的所以相关函数，选择作为父类主要是单机对战和网络对战类都可以继承这个类，实现对不同功能的封装。

继承Connector类，实现和服务器连接的功能

******************/

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 9088


/*
线程函数 友元
*/
int recvThread(void *data);


class NetScene : public Scene, Room, Connector
{
	friend int recvThread(void*data);
public:
	NetScene();
	~NetScene();

	/*
	逻辑处理函数 virtual
	*/
	void logic();

	/*
	渲染处理函数 virtual
	*/
	void render();

	/*
	执行游戏逻辑
	*/
	virtual void frame();
private:
	/*
	处理wait 的逻辑
	*/
	virtual void waitState();

	/*
	处理start 的逻辑
	*/
	virtual void startState();

	/*
	处理run 的逻辑
	*/
	virtual void runState() ;

	/*
	接收服务器消息
	*/
	virtual void recvData();

	/*
	判断游戏状态
	*/
	bool checkGameState();

	/*
	解析waitMessage
	*/
	void getWaitMessage(const WaitMessageStruct &message);

	/*
	接收玩家1和玩家2的消息
	*/
	void recvPlayerMessage();

	/*
	初始化button
	*/
	void initButton();

	/*
	回调函数
	*/
	void prepareBtnCallBack();
private:
	/*我的编号
	*/
	int myIndex;

	/*准备button
	*/
	Button *prepareBtn;

	/*
	线程相关函数
	*/
	SDL_Thread *thread;
	/*退出标识
	*/
	bool threadQuit;
	void initThread();
	void releareThread();
	
};



#endif // !__NETSCENE__H__
