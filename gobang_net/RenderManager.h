#pragma once
#ifndef __RENDERMANAGER__H__
#define __RENDERMANAGER__H__

#include "define.h"
#include "MyWindow.h"

class RenderManager
{
public:
	RenderManager();
	~RenderManager() {

	}

	void rendEverything();

private:
	shared_ptr<MyWindow> winRender;


};

















#endif  //__RENDERMANAGER__H__