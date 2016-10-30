#include "BeginScene.h"



void BeginScene::init() {
	auto winMgr = WindowManager::get();
	try {
		picture = winMgr->loadImage(BEGINSCENE_FILE);

	} catch (const runtime_error &e) {
		cout << e.what() << endl;
		return;
	}
	initButton();
}


void BeginScene::initButton() {

	singleBtn = Button::create(BUTTON_NORMAL_FILE, BUTTON_SELECTED_FILE, BUTTON_DISABLE_FILE);
	singleBtn->setPosition(210, 380);
	singleBtn->setTitle("人机对战", SDL_Color{ 0, 0, 0 },20);
	singleBtn->setCallback(CALLBACK_0(BeginScene::singleMode, this));
	this->addButton(singleBtn);

	netBtn = Button::create(BUTTON_NORMAL_FILE, BUTTON_SELECTED_FILE, BUTTON_DISABLE_FILE);
	netBtn->setPosition(210, 430);
	netBtn->setTitle("联网对战", SDL_Color{ 0,0,0 }, 20);
	netBtn->setCallback(CALLBACK_0(BeginScene::netMode, this));
	this->addButton(netBtn);
}


void BeginScene::logic() {
	checkButtonClick();
}


void BeginScene::render() {
	auto renderer = WindowManager::get();

	renderer->draw(picture, SDL_Rect{ 0,0,WIN_WIDTH ,WIN_HEIGHT });
	btnCollection->render();
}

/**********************
回调函数
**********************/
/*
单机模式
*/
void BeginScene::singleMode() {
	cout << "singleMode" << endl;
}

/*
联机模式
*/
void BeginScene::netMode() {
	cout << "netMode" << endl;

	/*singleBtn->setDisabled(true);
	netBtn->setDisabled(true);*/

	auto sceneMgr = SceneManager::get();
	sceneMgr->push(new NetScene());
}