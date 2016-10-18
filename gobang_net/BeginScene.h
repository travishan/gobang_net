#pragma once
#ifndef __BEGINSCENE__H__
#define __BEGINSCENE__H__


#include "define.h"
#include "ButtonManager.h"
#include "WindowManager.h"


class BeginScene : Manager
{
	SingletonBuilder(BeginScene)
public:
	BeginScene() :picture(nullptr),singleBtn(nullptr),netBtn(nullptr){}
	~BeginScene() {}

	
	
	void render();

	virtual void startUp();
	virtual void shutDown();
private:
	SDL_Texture *picture;
	Button *singleBtn, *netBtn;


	void init();
	void singleMode();
	void netMode();
	void initButton();

};





















#endif // !__BEGINSCENE__H__
