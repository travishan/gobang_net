#pragma once
#ifndef __RENDERMANAGER__H__
#define __RENDERMANAGER__H__


#include "Manager.h"
#include "WindowManager.h"
#include "ButtonManager.h"

class RenderManager : Manager
{
	SingletonBuilder(RenderManager)
public:
	RenderManager() {

	}
	~RenderManager() {

	}
	virtual void startUp();
	virtual void shutDown();


	void rendEverything();

	
private:
	WindowManager *winMgr;
	ButtonManager *btnMgr;


};

















#endif  //__RENDERMANAGER__H__