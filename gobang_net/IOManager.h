#ifndef __IOMANAGER__H__
#define __IOMANAGER__H__


#include "Manager.h"
#include "ButtonCollection.h"

class IOManager : public Manager
{
	PropertyBuilderByName(bool, quit, Quit, private)
	PropertyBuilderByName(bool, mouseLeftDown, MouseLeftDown, private)
	PropertyBuilderByName(bool, mouseLeftUp, MouseLeftUp, private)
	//PropertyBuilderByName(TextInput*, textInput, TextInput, private)
	SingletonBuilder(IOManager)
public:
	IOManager() :quit(0), mouseLeftDown(false), mouseLeftUp(false) {}
	~IOManager() {}

	virtual void startUp();
	virtual void shutDown();

	void input(bool &quit);
	void resetMouse() {
		mouseLeftDown = mouseLeftUp = false;
	}

	void addMouseFunc(const function<void()>&);
	
private:
	SDL_Event e;
	vector<function<void()>> mouseFuncVec;
};












#endif // !__IOMANAGER__H__
