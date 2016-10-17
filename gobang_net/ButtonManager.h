#pragma once
#ifndef __BUTTONMANAGER__H__
#define __BUTTONMANAGER__H__

#include "Manager.h"
#include "WindowManager.h"


class Button
{
	PropertyBuilderByName(bool, selected, Selected)
public:
	Button() : x(0),y(0), w(0), h(0), selected(false),disable(false) {}
	virtual ~Button() {}

	//����һ����ť
	static Button* create(const string &normalImage, const string &selectedImage = "", const string &disableImage = "") {
		Button* button = new Button();
		button->init(normalImage, selectedImage, disableImage);
		return button;
	}

	//��ӻص�����
	void addCallback(function<void()> f);

	//����λ��
	void setPosition(int x, int y);
	//��Ⱦ��ť
	void render();
	//�������Ƿ��ڰ�ť��
	bool hit(int mX, int mY);
	//���ûص�����
	void callBackFun();
	
protected:
	void init(const string &normalImage, const string &selectedImage, const string &disableImage);
	

protected:
	int x, y, w, h;
	bool disable;
	SDL_Texture *normalTex, *selectedTex, *disableTex;
	function<void()> callBack;
};


class ButtonManager : public Manager
{
	SingletonBuilder(ButtonManager)
public:

	virtual void startUp();
	virtual void shutDown();


	//��Ӱ�ť����ť����
	void addButton(Button *button);

	//��Ⱦ����Button
	void render();

	//�������¼�
	void checkClick(bool mouseLeftDown, bool mouseLeftUp);

	//�������а�ťselectedΪfalse
	void setSelectedFalse();


private:
	vector<Button*> buttons;
};

















#endif // !__BUTTONMANAGER__H__
