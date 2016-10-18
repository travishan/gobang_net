#include "BeginScene.h"

void BeginScene::startUp() {
	init();
}

void BeginScene::shutDown() {

	delete BeginScene::get();
}


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
	auto btnMgr = ButtonManager::get();

	singleBtn = Button::create(BUTTON_NORMAL_FILE, BUTTON_SELECTED_FILE, BUTTON_DISABLE_FILE);
	singleBtn->setPosition(210, 380);
	singleBtn->setTitle("P vs C", SDL_Color{ 0,0,0 },24);
	singleBtn->setCallback(CALLBACK_0(BeginScene::singleMode, this));
	btnMgr->addButton(singleBtn);

	netBtn = Button::create(BUTTON_NORMAL_FILE, BUTTON_SELECTED_FILE, BUTTON_DISABLE_FILE);
	netBtn->setPosition(210, 440);
	netBtn->setTitle("P vs P", SDL_Color{ 0,0,0 }, 24);
	netBtn->setCallback(CALLBACK_0(BeginScene::netMode, this));
	btnMgr->addButton(netBtn);
}

void BeginScene::render() {
	auto renderer = WindowManager::get();
	//renderer->draw(0, 0, picture);
	renderer->draw(picture, SDL_Rect{ 0,0,WIN_WIDTH ,WIN_HEIGHT });
}

void BeginScene::singleMode() {
	cout << "singleMode" << endl;
}


void BeginScene::netMode() {
	cout << "netMode" << endl;
}