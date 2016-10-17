#include "ButtonManager.h"




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
void Button::addCallback(function<void()> f) {
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
}

bool Button::hit(int mX, int mY) {
	if (mX >= x && mX <= (x + w) && mY >= y && mY <= (y + h)) {
		return true;
	}
	return false;
}

void Button::callBackFun() {
	callBack();
}







void ButtonManager::startUp() {

	//nothing to do for now

}


void ButtonManager::shutDown() {
	for (Button* btn : buttons) {
		delete btn;
	}
	buttons.clear();
	delete get();
}


void ButtonManager::addButton(Button *button) {
	if (button == nullptr) {
		return;
	}
	buttons.push_back(button);
}

void ButtonManager::render() {
	for (Button *b : buttons) {
		b->render();
	}
}


void ButtonManager::checkClick(bool mouseLeftDown,bool mouseLeftUp) {
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
					b->callBackFun();
				}
			}
		} else if (b->getSelected() && mouseLeftUp) {
			b->setSelected(!mouseLeftUp);
		}
	}
}

void ButtonManager::setSelectedFalse() {
	for (Button *b : buttons) {
		b->setSelected(false);
	}
}