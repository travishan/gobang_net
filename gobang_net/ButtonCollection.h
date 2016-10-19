#pragma once
#ifndef __BUTTONMANAGER__H__
#define __BUTTONMANAGER__H__


#include "define.h"
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

	//����һ����ť
	static Button* create(const string &normalImage, const string &selectedImage = "", const string &disableImage = "") {
		Button* button = new Button();
		button->init(normalImage, selectedImage, disableImage);
		return button;
	}

	//��ӻص�����
	void setCallback(function<void()> f);
	//����λ��
	void setPosition(int x, int y);
	//��Ⱦ��ť
	void render();
	//�������Ƿ��ڰ�ť��
	bool hit(int mX, int mY);
	//���ûص�����
	void runCallBack();
	//����title
	void setTitle(const string &str, const SDL_Color &color, int size);
	
protected:
	void init(const string &normalImage, const string &selectedImage, const string &disableImage);
	

protected:
	string title;
	int x, y, w, h, tw, th;
	SDL_Texture *normalTex, *selectedTex, *disableTex, *titleTex;
	function<void()> callBack;
};


class ButtonCollection
{
public:
	ButtonCollection() {}
	~ButtonCollection(){
		for (Button* btn : buttons) {
			delete btn;
		}
		buttons.clear();
	}


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
