#ifndef __NETSCENE__H__
#define __NETSCENE__H__

#include "define.h"
#include "Room.h"
#include "Connector.h"
#include "SceneManager.h"



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
	virtual void waitStateRender();

	/*
	处理start 的逻辑
	*/
	virtual void startState();
	virtual void startStateRender();

	/*
	处理run 的逻辑
	*/
	virtual void runState() ;
	virtual void runStateRender();

	/*
	处理end 的逻辑
	*/
	virtual void endState();
	virtual void endStateRender();
	/*
	解析PlayerMessage
	*/
	void setPlayerMessage(const Player_Message &message);
	/*
	解析GameMessage
	*/
	void setGameMessage(const Game_Message &message);

	/*
	初始化button
	*/
	void initButton();

	/*
	回调函数
	*/
	void prepareBtnCallBack();

	/*
	根据服务器消息设置敌手的棋子
	*/
	void setAnotherPoint(B_POINT point);

private:

	/*准备button
	*/
	Button *prepareBtn;

	/*
	线程相关变量 和 函数
	*/
	SDL_Thread *thread,*sendThread;
	bool threadQuit;//退出线程标识
	bool sendFlag;//发送标识

	void initThread();//初始化线程
	void releaseThread();//释放线程变量

};



#endif // !__NETSCENE__H__
