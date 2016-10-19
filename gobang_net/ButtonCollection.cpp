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
		disableTex = winMgr->loadImage(disableImage);
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
	if (disable) {
		renderer->draw(x, y, disableTex);
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
		b->render();
	}
}


void ButtonCollection::checkClick(bool mouseLeftDown,bool mouseLeftUp) {
	int x, y;
	SDL_GetMouseState(&x, &y);

	for (Button *b : buttons) {
		if (b->hit(x, y)) {
			if (!b->getSelected()) {
				if (mouseLeftDown) {
					b->setSelected(mouseLeftDown);
				}
			} else {
				if (mouseLeftUp) {
					b->setSelected(!mouseLeftUp);
					b->runCallBack();
				}
			}
		} else if (b->getSelected() && mouseLeftUp) {
			b->setSelected(!mouseLeftUp);
		}
	}
}

void ButtonCollection::setSelectedFalse() {
	for (Button *b : buttons) {
		b->setSelected(false);
	}
}