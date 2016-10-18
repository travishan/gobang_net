#pragma once
#ifndef __FRAMEMANAGER__H__
#define __FRAMEMANAGER__H__

#include "Manager.h"
#include "Board.h"
#include "ButtonManager.h"
#include "IOManager.h"
#include "BeginScene.h"

class FrameManager : public Manager
{
	SingletonBuilder(FrameManager)
public:
	FrameManager() {

	}
	~FrameManager() {

	}
	virtual void startUp();
	virtual void shutDown();

	void frame();
private:
	ButtonManager *btnMgr;
	IOManager *IOMgr;

	BeginScene *bgnScene;

};








 













#endif // !__FRAMEMANAGER__H__
