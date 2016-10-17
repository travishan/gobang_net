#pragma once
#ifndef __FRAMEMANAGER__H__
#define __FRAMEMANAGER__H__

#include "Manager.h"
#include "Board.h"

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
	Board *board;

};








 













#endif // !__FRAMEMANAGER__H__
