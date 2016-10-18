#pragma once
#ifndef __BUTTONMANAGER__H__
#define __BUTTONMANAGER__H__

#include "Manager.h"
#include "WindowManager.h"


class Button
{
	PropertyBuilderByName(bool, selected, Selected)
	PropertyBuilderByName(bool, disable, Disable)
public:
	Button() : selected(false), disable(false), title(""), x(0),y(0), w(0), h(0),
		normalTex(nullptr),selectedTex(nullptr),disableTex(nullptr),titleTex(nullptr)
	{}
	virtual ~Button() {}

	//创建一个按钮
	static Button* create(const string &normalImage, const string &selectedImage = "", const string &disableImage = "") {
		Button* button = new Button();
		button->init(normalImage, selectedImage, disableImage);
		return button;
	}

	//添加回调函数
	void addCallback(function<void()> f);
	//设置位置
	void setPosition(int x, int y);
	//渲染按钮
	void render();
	//检查鼠标是否在按钮中
	bool hit(int mX, int mY);
	//调用回调函数
	void callBackFun();
	//设置title
	void setTitle(string str, SDL_Color color, int size);
	
protected:
	void init(const string &normalImage, const string &selectedImage, const string &disableImage);
	

protected:
	string title;
	int x, y, w, h, tw, th;
	SDL_Texture *normalTex, *selectedTex, *disableTex, *titleTex;
	function<void()> callBack;
};


class ButtonManager : public Manager
{
	SingletonBuilder(ButtonManager)
public:

	virtual void startUp();
	virtual void shutDown();


	//添加按钮到按钮队列
	void addButton(Button *button);

	//渲染所有Button
	void render();

	//检查鼠标事件
	void checkClick(bool mouseLeftDown, bool mouseLeftUp);

	//设置所有按钮selected为false
	void setSelectedFalse();


private:
	vector<Button*> buttons;
};

















#endif // !__BUTTONMANAGER__H__
