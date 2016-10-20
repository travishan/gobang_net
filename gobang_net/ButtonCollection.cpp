#include "ButtonCollection.h"


/********************************

Button

*********************************/

void Button::init(const string &normalImage, const string &selectedImage, const string &disableImage) {
	auto winMgr = WindowManager::get();
	
	try {
		normalTex = winMgr->loadImage(normalImage);
		SDL_QueryTexture(normalTex, nullptr, nullptr, &w, &h);
	} catch (const runtime_error &e) {
		cout << e.what() << endl;
	}
	try {
		selectedTex = winMgr->loadImage(selectedImage);
	} catch (const runtime_error &e) {
		cout << e.what() << endl;
	}
	try {
		disabledTex = winMgr->loadImage(disableImage);
	} catch (const runtime_error &e) {
		cout << e.what() << endl;
	}
}

//添加回调函数
void Button::setCallback(function<void()> f) {
	callBack = f;
}

//设置位置
void Button::setPosition(int x, int y) {
		this->x = x;
		this->y = y;
}

//渲染按钮
void Button::render() {
	auto renderer = WindowManager::get();
	if (disabled) {
		renderer->draw(x, y, disabledTex);
	} else if (selected) {
		renderer->draw(x, y, selectedTex);
	} else {
		renderer->draw(x, y, normalTex);
	}
	renderer->draw(x + (w - tw) / 2, y + (h - th) / 2, titleTex);
	//renderer->draw(x, y, titleTex);
}

bool Button::hit(int mX, int mY) {
	if (mX >= x && mX <= (x + w) && mY >= y && mY <= (y + h)) {
		return true;
	}
	return false;
}

void Button::runCallBack() {
	callBack();
}

void Button::setTitle(const string &str, const SDL_Color &color,int size) {
	auto winMgr = WindowManager::get();

	title = str;
	try {
		auto tex = winMgr->renderText(str, TTF_FILE, color, size);
		SDL_DestroyTexture(titleTex);
		titleTex = tex;
		SDL_QueryTexture(titleTex, nullptr, nullptr, &tw, &th);
	} catch (const runtime_error &e) {
		cout << e.what() << endl;
	}
	
}

/********************************

TextInput

*********************************/

//渲染按钮
void TextInput::render() {
	
	auto renderer = WindowManager::get();
	if (disabled) {
		renderer->draw(x, y, disabledTex);
	} else if (selected) {
		renderer->draw(x, y, selectedTex);
	} else {
		renderer->draw(x, y, normalTex);
	}
	renderer->draw(x, y + (h - th) / 2, titleTex);
}

//检查鼠标是否在按钮中
bool TextInput::hit(int mX, int mY) {
	if (mX >= x && mX <= (x + w) && mY >= y && mY <= (y + h)) {
		//SDL_StartTextInput();
		//method 2   SDL_SetTextInputRect 
		return true;
	}
	SDL_StopTextInput();
	return false;
}

void TextInput::append(string s) {
	title.append(s);
	this->setTitle(title, SDL_Color{ 255,255,255 }, 16);
}

/********************************

ButtonCollection

*********************************/


void ButtonCollection::addButton(Button *button) {
	if (button == nullptr) {
		return;
	}
	buttons.push_back(button);
}

void ButtonCollection::render() {
	for (Button *b : buttons) {
		if (!b->getDisabled()) {
			b->render();
		}
	}
}


void ButtonCollection::checkClick(bool mouseLeftDown,bool mouseLeftUp) {
	int x, y;
	SDL_GetMouseState(&x, &y);

	if (!mouseLeftDown && !mouseLeftUp) {
		return;
	}
	for (int i = 0; i < buttons.size(); ++i) {
		if (!buttons[i]->getDisabled()) {
			if (mouseLeftDown) {
				if (buttons[i]->hit(x, y) && !buttons[i]->getSelected()) {
					buttons[i]->setSelected(true);
				}
			} else if (mouseLeftUp) {
				if (buttons[i]->hit(x, y)) {
					if (buttons[i]->getSelected()) {
						buttons[i]->setSelected(false);
						buttons[i]->runCallBack();
					} else {
						buttons[i]->setSelected(false);
					}
				}
			}
		}
	}
}

void ButtonCollection::setSelectedFalse() {
	for (Button *b : buttons) {
		b->setSelected(false);
	}
}