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
	netBtn->setPosition(210, 420);
	netBtn->setTitle("联网对战", SDL_Color{ 0,0,0 }, 20);
	netBtn->setCallback(CALLBACK_0(BeginScene::netMode, this));
	this->addButton(netBtn);

	serverBtn = Button::create(BUTTON_NORMAL_FILE, BUTTON_SELECTED_FILE, BUTTON_DISABLE_FILE);
	serverBtn->setPosition(210, 460);
	serverBtn->setTitle("创建房间", SDL_Color{ 0,0,0 }, 20);
	serverBtn->setCallback(CALLBACK_0(BeginScene::createRoom, this));
	this->addButton(serverBtn);
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

	singleBtn->setDisabled(true);
	netBtn->setDisabled(true);
	serverBtn->setDisabled(true);

	textInput = TextInput::create(BUTTON_NORMAL_FILE, BUTTON_SELECTED_FILE);
	textInput->setPosition(210, 440);
	textInput->setCallback(CALLBACK_0(BeginScene::startText, this));
	this->addButton(textInput);
	auto ioMgr = IOManager::get();
	ioMgr->setTextInput(textInput);

	conBtn = Button::create(BUTTON_NORMAL_FILE, BUTTON_SELECTED_FILE, BUTTON_DISABLE_FILE);
	conBtn->setPosition(350, 440);
	conBtn->setTitle("连接", SDL_Color{ 0,0,0 }, 20);
	conBtn->setCallback(CALLBACK_0(BeginScene::connect, this));
	this->addButton(conBtn);
}

void BeginScene::startText() {
	SDL_StartTextInput();
}

void BeginScene::connect() {
	cout << "connect" << endl;
}

void BeginScene::createRoom() {
	cout << "create" << endl;
}