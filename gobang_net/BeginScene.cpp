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
	singleBtn->setTitle("P vs C", SDL_Color{ 0,0,0 },24);
	singleBtn->setCallback(CALLBACK_0(BeginScene::singleMode, this));
	this->addButton(singleBtn);

	netBtn = Button::create(BUTTON_NORMAL_FILE, BUTTON_SELECTED_FILE, BUTTON_DISABLE_FILE);
	netBtn->setPosition(210, 440);
	netBtn->setTitle("P vs P", SDL_Color{ 0,0,0 }, 24);
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

void BeginScene::singleMode() {
	cout << "singleMode" << endl;
}


void BeginScene::netMode() {
	cout << "netMode" << endl;
}