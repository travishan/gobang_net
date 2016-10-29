#ifndef __IOMANAGER__H__
#define __IOMANAGER__H__


#include "Manager.h"
#include "ButtonCollection.h"

class IOManager : public Manager
{
	PropertyBuilderByName(bool, quit, Quit, private)
	PropertyBuilderByName(bool, mouseLeftDown, MouseLeftDown, private)
	PropertyBuilderByName(bool, mouseLeftUp, MouseLeftUp, private)
	PropertyBuilderByName(TextInput*, textInput, TextInput, private)
	SingletonBuilder(IOManager)
public:
	IOManager() :quit(0), mouseLeftDown(false), mouseLeftUp(false), textInput(nullptr) {}
	~IOManager() {}

	virtual void startUp();
	virtual void shutDown();

	void input(bool &quit);
	void resetMouse() {
		mouseLeftDown = mouseLeftUp = false;
	}
	
private:
	SDL_Event e;
};












#endif // !__IOMANAGER__H__
