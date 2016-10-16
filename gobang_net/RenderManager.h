#pragma once
#ifndef __RENDERMANAGER__H__
#define __RENDERMANAGER__H__

#include "define.h"
#include "MyWindow.h"
#include "Manager.h"

class RenderManager : Manager
{
public:
	RenderManager() {

	}
	 ~RenderManager() {

	}
	virtual void startUp();
	virtual void shutDown();


	void rendEverything();
private:
	shared_ptr<MyWindow> winRender;


};

















#endif  //__RENDERMANAGER__H__