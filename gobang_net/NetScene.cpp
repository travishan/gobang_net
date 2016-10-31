#include "NetScene.h"




NetScene::NetScene() : prepareBtn(nullptr), thread(nullptr), sendThread(nullptr), threadQuit(false), sendFlag(false){
	Connector::connect(SERVER_IP, SERVER_PORT);
	Room::loadAll();
	initButton();
	initThread();
}

NetScene::~NetScene() {
	Connector::disconnect();
	releaseThread();
}

/*
逻辑处理函数  virtual
*/
void NetScene::logic() {
	frame();
	checkButtonClick();
}

/*
渲染处理函数 virtual
*/
void NetScene::render() {
	Room::renderBoard();
	switch (gameState) {
	case WAIT:
		waitStateRender();
		break;
	case START:
		startStateRender();
		break;
	case RUN:
		runStateRender();
		break;
	case REGRET:
		break;
	case END:
		endStateRender();
		break;
	}
	btnCollection->render();
}

/*
游戏渲染
*/
void NetScene::waitStateRender() {
	auto winMgr = WindowManager::get();
	auto text = winMgr->renderText("准备阶段", TTF_FILE, SDL_Color{ 255,0,0 }, 24);
	winMgr->draw(200, 100, text);
}

void NetScene::startStateRender() {
	auto winMgr = WindowManager::get();
	auto text = winMgr->renderText("开始阶段", TTF_FILE, SDL_Color{ 255,0,0 }, 24);
	winMgr->draw(200, 100, text);
	SDL_DestroyTexture(text);
}

void NetScene::runStateRender() {
	auto winMgr = WindowManager::get();
	auto text = winMgr->renderText("游戏进行阶段", TTF_FILE, SDL_Color{ 255,0,0 }, 24);
	winMgr->draw(200, 100, text);
	SDL_DestroyTexture(text);
}

void NetScene::endStateRender() {
	auto winMgr = WindowManager::get();
	auto text = winMgr->renderText("游戏结束", TTF_FILE, SDL_Color{ 255,0,0 }, 24);
	winMgr->draw(200, 100, text);
	SDL_DestroyTexture(text);
	if (winner != 65535) {
		auto winMgr = WindowManager::get();
		SDL_Texture *texture;
		if (winner == myIndex) {
			texture = winMgr->renderText("你赢了", TTF_FILE, SDL_Color{ 255,0,0 }, 24);
		} else {
			texture = winMgr->renderText("你输了", TTF_FILE, SDL_Color{ 255,0,0 }, 24);
		}
		winMgr->draw(300, 100, texture);
		SDL_DestroyTexture(texture);
	}
	
}

/*
执行游戏逻辑
*/
void NetScene::frame() {
	switch (gameState) {
	case WAIT:
		waitState();
		break;
	case START:
		startState();
		break;
	case RUN:
		runState();
		break;
	case REGRET:
		break;
	case END:
	{
		//cout << "游戏结束" << endl;
	}
		break;
	}
}

/*
解析GameMessage
*/
void NetScene::setGameMessage(const Game_Message &message) {
	gameState = (GameState)message.gameState;
	p1Index = message.p1Index;
	p2Index = message.p2Index;
	currentPlayer = message.curSide;
	playerNum = message.playerNum;
	lastTime = message.time;
	winner = message.winner;
}

/*
解析waitMessage
*/
void NetScene::setPlayerMessage(const Player_Message &message) {
	myIndex = message.yourIndex;
	int playerIndex = message.playerIndex;
	Player *p = nullptr;
	if (playerIndex == p1Index){
		if (p1 == nullptr) {
			p1 = make_shared<Player>(Player());
		}
		p = p1.get();
	} else if(playerIndex == p2Index){
		if (p2 == nullptr) {
			p2 = make_shared<Player>(Player());
		}
		p = p2.get();
	} else {
		return;
	}
	p->setColor((CHESS_COLOR)message.color);
	char name[16];
	memcpy(name, message.name, 16);
	p->setName(name);
	p->setConnected((bool)message.connected);
	p->setRegret((bool)message.regret);
	p->setDisconnected((bool)message.disconnected);
	p->setRoomIndex((uint16_t)message.roomIndx);
	p->setPrepared((bool)message.prepared);
}

/*
处理wait 的逻辑
*/
void NetScene::waitState() {
	/*cout << "现在是等待状态" << endl;
	cout << "current player number : " << playerNum;
	cout << "p1Index : " << p1Index << ", p2Index :" << p2Index << endl << endl;*/
}

/*
处理start 的逻辑
*/
void NetScene::startState() {
	
}

/*
处理Run 的逻辑
*/
void NetScene::runState() {
	if (Room::play()) {
		sendFlag = true;
		changeSide();
	}
	
}

/*
处理end 的逻辑
*/
void NetScene::endState() {
	if (winner != 65535) {
		
	}
}


/***********************

初始化函数

************************/


/*
初始化button
*/
void NetScene::initButton() {
	prepareBtn = Button::create(BUTTON_NORMAL_FILE, BUTTON_SELECTED_FILE, BUTTON_DISABLE_FILE);
	prepareBtn->setPosition(210, 380);
	prepareBtn->setTitle("准备", SDL_Color{ 0, 0, 0 }, 20);
	prepareBtn->setCallback(CALLBACK_0(NetScene::prepareBtnCallBack, this));
	this->addButton(prepareBtn);
}

/*
回调函数
*/
void NetScene::prepareBtnCallBack() {
	FlagType flag = FLAG_READY;
	client.sendData(nullptr, 0, flag);
	prepareBtn->setDisabled(true);
}

/*
根据服务器消息设置敌手的棋子
*/
void NetScene::setAnotherPoint(B_POINT point) {
	auto p = getAnotherPlayer(myIndex);
	if (p == nullptr) return;
	auto color = p->getColor();
	chessBoard[point.row][point.col] = color;
	p->push_back(point);
}



/*
线程函数  负责接收从服务器发来的消息，并进行解析
GameMessage 当前游戏相关信息
PlayerMessage 当前玩家相关信息
PlayMessage 走棋方相关信息
RegretMessage 悔棋相关信息
*/

int recvThreadFunc(void *data) {
	NetScene *netScene = (NetScene*)data;
	FlagType flag = 0;
	DataType recvData = nullptr;
	LengthType length = 0;
	while (!netScene->threadQuit) {
		recvData = netScene->client.recvData(flag, length);
		switch (flag) {
		case FLAG_GAME_INFO:
		{
			Game_Message msg;
			memcpy(&msg, recvData, length);
			netScene->setGameMessage(msg);
			if (recvData) delete recvData;
		}break;
		case FLAG_PLAYER_INFO:
		{
			Player_Message msg;
			memcpy(&msg, recvData, length);
			netScene->setPlayerMessage(msg);
			char name[16];
			memcpy(name, msg.name, 16);
			if(recvData) delete recvData;
		}break;
		case FLAG_PLAY_INFO:
		{
			B_POINT point;
			memcpy(&point, recvData, length);
			netScene->setAnotherPoint(point);
			cout << "row: " << point.row << " col: " << point.col << endl;
			if (recvData) delete recvData;
		}
			break;
		case FLAG_QUERY_REGRET:
			break;
		}
	}
	return 0;
}

int sendThreadFunc(void *data) {
	NetScene *netScene = (NetScene*)data;
	while (!netScene->threadQuit) {
		if (netScene->sendFlag) {
			auto my = netScene->getPlayer(netScene->myIndex);
			auto p = *(my->end() - 1);
			DataType data = new uint8_t[sizeof(B_POINT)];
			memcpy(data, &p, sizeof(B_POINT));
			netScene->client.sendData(data, sizeof(B_POINT), FLAG_PLAY);
			delete data;
			netScene->sendFlag = false;
		}
	}
	return 0;
}

void NetScene::initThread() {
	//创建并运行线程
	thread = SDL_CreateThread(recvThreadFunc, "recvThread", this);
	sendThread = SDL_CreateThread(sendThreadFunc, "sendThread", this);
}

void NetScene::releaseThread() {
	threadQuit = true;
}