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
	//backgroundͼƬ
	SDL_Texture *picture;
	//������ť   ����ģʽ������ģʽ
	Button *singleBtn, *netBtn;


	//��ʼ��
	void init();
	//��ʼ����ť
	void initButton();
	//����ģʽ
	void singleMode();
	//����ģʽ
	void netMode();


};





#endif // !__BEGINSCENE__H__
