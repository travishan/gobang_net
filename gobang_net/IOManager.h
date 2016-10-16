#pragma once
#ifndef __IOMANAGER__H__
#define __IOMANAGER__H__


#include "Manager.h"

class IOManager : Manager
{
	PropertyBuilderByName(bool, quit, Quit)
	SingletonBuilder(IOManager)
public:
	IOManager() {}
	~IOManager() {}

	virtual void startUp();
	virtual void shutDown();

	void input(bool &quit);
	
private:
	SDL_Event e;

};












#endif // !__IOMANAGER__H__
