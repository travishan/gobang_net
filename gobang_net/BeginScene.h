#pragma once
#ifndef __BEGINSCENE__H__
#define __BEGINSCENE__H__


#include "define.h"
#include "WindowManager.h"
#include "SceneManager.h"



class BeginScene : public Scene
{
public:
	BeginScene() :picture(nullptr),singleBtn(nullptr),netBtn(nullptr){
		init();
	}
	~BeginScene() {}

	virtual void logic();
	virtual void render();

private:
	SDL_Texture *picture;
	Button *singleBtn, *netBtn;


	void init();
	void singleMode();
	void netMode();
	void initButton();

};





#endif // !__BEGINSCENE__H__
