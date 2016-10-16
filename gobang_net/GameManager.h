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
	GameState gameState;
	bool quit;
};




#endif  //__GAMEMANAGER__H__