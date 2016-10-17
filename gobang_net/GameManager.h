#pragma once
#ifndef __GAMEMANAGER__H__
#define __GAMEMANAGER__H__


#include "WindowManager.h"
#include "RenderManager.h"
#include "IOManager.h"
#include "FrameManager.h"

/********************************
��Ϸ���
********************************/
class GameManager
{
public:
	GameManager() :gameState(Select), quit(false) {}

	void run();
private:
	void before();
	void after();
private:
	GameState gameState;
	bool quit;


private://Mgr
	WindowManager *winMgr;
	RenderManager *renderMgr;
	IOManager *ioMgr;
	FrameManager *frameMgr;
};




#endif  //__GAMEMANAGER__H__