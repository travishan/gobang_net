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
	~BeginScene() {
		Scene::~Scene();
		SDL_DestroyTexture(picture);
	}

	virtual void logic();
	virtual void render();

private:
	//background图片
	SDL_Texture *picture;
	//两个按钮   单人模式和联机模式
	Button *singleBtn, *netBtn;


	//初始化
	void init();
	//初始化按钮
	void initButton();
	//单机模式
	void singleMode();
	//联机模式
	void netMode();


};





#endif // !__BEGINSCENE__H__
