#ifndef __RENDERMANAGER__H__
#define __RENDERMANAGER__H__


#include "Manager.h"
#include "WindowManager.h"
#include "SceneManager.h"

class RenderManager : public Manager
{
	SingletonBuilder(RenderManager)
public:
	RenderManager() {

	}
	~RenderManager() {

	}
	virtual void startUp();
	virtual void shutDown();


	void rendEverything(const GameState &state);

	
private:
	WindowManager *winMgr;

};

















#endif  //__RENDERMANAGER__H__