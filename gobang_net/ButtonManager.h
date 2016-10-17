#pragma once
#ifndef __BUTTONMANAGER__H__
#define __BUTTONMANAGER__H__

#include "Manager.h"
#include "WindowManager.h"


class Button
{
public:
	Button() : selected(false) {}
	virtual ~Button() {}

	//创建一个按钮
	static Button* create(const string &normalImage, const string &selectedImage = "", const string &disableImage = "") {
		Button* button = new Button();
		button->init(normalImage, selectedImage, disableImage);

	}

	void setRect(SDL_Rect rect) {
		rect = rect;
	}

	void addToBtnMgr();
protected:
	void init(const string &normalImage, const string &selectedImage, const string &disableImage);
	

protected:
	SDL_Rect rect;
	bool selected;
	SDL_Texture *normalTex, *selectedTex, *disableTex;
};


class ButtonManager : public Manager
{
	SingletonBuilder(ButtonManager)
public:

	virtual void startUp();
	virtual void shutDown();

private:
	vector<
};

















#endif // !__BUTTONMANAGER__H__
