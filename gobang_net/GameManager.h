#pragma once
#ifndef __GAMEMANAGER__H__
#define __GAMEMANAGER__H__


#include"define.h"
#include "RenderManager.h"

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
	RenderManager *renderMgr;
};




#endif  //__GAMEMANAGER__H__