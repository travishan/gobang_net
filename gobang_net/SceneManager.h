#pragma once
#ifndef __SCENEMANAGER__H__
#define __SCENEMANAGER__H__

#include "define.h"
#include "Manager.h"
#include "ButtonCollection.h"
#include "IOManager.h"


class Scene
{
public:
	Scene() :btnCollection(new ButtonCollection) {}
	virtual ~Scene() {}

	virtual void logic() = 0;
	virtual void render() = 0;
	virtual void checkButtonClick();


	void addButton(Button *btn);

	
protected:
	ButtonCollection *btnCollection;
};



class SceneManager : Manager
{
	SingletonBuilder(SceneManager)
public:
	virtual void startUp();
	virtual void shutDown();

	Scene* front();
	void push(Scene* scene);
private:
	stack<Scene*> sceneStack;
};




#endif // !__SCENEMANAGER__H__
