#pragma once
#ifndef __IOMANAGER__H__
#define __IOMANAGER__H__


#include "Manager.h"


class IOManager : public Manager
{
	PropertyBuilderByName(bool, quit, Quit)
	PropertyBuilderByName(bool, mouseLeftDown, MouseLeftDown)
	PropertyBuilderByName(bool, mouseLeftUp, MouseLeftUp)
	SingletonBuilder(IOManager)
public:
	IOManager() :quit(0), mouseLeftDown(false), mouseLeftUp(false){}
	~IOManager() {}

	virtual void startUp();
	virtual void shutDown();

	void input(bool &quit);
	
private:
	SDL_Event e;
	
};












#endif // !__IOMANAGER__H__
