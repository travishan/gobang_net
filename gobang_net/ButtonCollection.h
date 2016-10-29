#ifndef __BUTTONMANAGER__H__
#define __BUTTONMANAGER__H__


#include "define.h"
#include "WindowManager.h"

class Button
{
	PropertyBuilderByName(bool, selected, Selected, protected)
	PropertyBuilderByName(bool, disabled, Disabled, protected)
public:
	Button() : selected(false), disabled(false), title(""), x(0),y(0), w(0), h(0),
		normalTex(nullptr),selectedTex(nullptr),disabledTex(nullptr),titleTex(nullptr)
	{}
	virtual ~Button() {}

	//创建一个按钮
	static Button* create(const string &normalImage, const string &selectedImage = "", const string &disableImage = "") {
		Button* button = new Button();
		button->init(normalImage, selectedImage, disableImage);
		return button;
	}

	//添加回调函数
	void setCallback(function<void()> f);
	//设置位置
	void setPosition(int x, int y);
	//渲染按钮
	virtual void render();
	//检查鼠标是否在按钮中
	virtual bool hit(int mX, int mY);
	//调用回调函数
	void runCallBack();
	//设置title
	void setTitle(const string &str, const SDL_Color &color, int size);
	const string& getTitle() const { return title; }
protected:
	void init(const string &normalImage, const string &selectedImage, const string &disableImage);
	

protected:
	string title;
	int x, y, w, h, tw, th;
	SDL_Texture *normalTex, *selectedTex, *disabledTex, *titleTex;
	function<void()> callBack;
};

class TextInput : public Button
{
public:
	TextInput() {

	}
	~TextInput() {}
	static TextInput* create(const string &normalImage, const string &selectedImage = "", const string &disableImage = "") {
		TextInput* ti = new TextInput();
		ti->init(normalImage, selectedImage, disableImage);
		return ti;
	}
	//渲染按钮
	void render();
	//检查鼠标是否在按钮中
	bool hit(int mX, int mY);
	//添加字符
	void append(string s);
protected:

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
