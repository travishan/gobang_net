#pragma once
#ifndef __GAMEMANAGER__H__
#define __GAMEMANAGER__H__


#include "WindowManager.h"
#include "RenderManager.h"
#include "IOManager.h"
#include "FrameManager.h"
#include "SceneManager.h"
#include "BeginScene.h"

/********************************
ÓÎÏ·Èë¿Ú
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
	SceneManager *sceneMgr;
	FrameManager *frameMgr;

	
};




#endif  //__GAMEMANAGER__H__