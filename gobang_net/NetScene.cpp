#include "NetScene.h"




NetScene::NetScene() : myIndex(-1), prepareBtn(nullptr), thread(nullptr), threadQuit(false){
	Connector::connect(SERVER_IP, SERVER_PORT);
	Room::loadAll();
	initButton();
	initThread();
}

NetScene::~NetScene() {
	Connector::disconnect();
	
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
	btnCollection->render();
}


/*
执行游戏逻辑
*/
void NetScene::frame() {
	recvData();
}


/*
接收服务器消息
*/
void NetScene::recvData() {
	//Room::checkDisconnect();
	
	if (!checkGameState()) {
		return;
	}
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
	{

	}
	break;
	case END:
	{
		cout << "有玩家断开连接" << endl;

	}
	break;
	}
}

/*
判断游戏状态
*/
bool NetScene::checkGameState() {
	if (flag == FLAG_WAIT || flag == FLAG_FULL) {
		gameState = WAIT;
	} else if (flag == FLAG_START) {
		gameState = START;
	} else if (flag == FLAG_RUN || flag == FLAG_CHANGE) {
		gameState = RUN;
	} else if (flag == FLAG_QUERY_REGRET || flag == FLAG_REGRETED) {
		gameState = REGRET;
	}else if (flag == FLAG_END) {
		gameState = END;
	} else {
		cerr << "错误：接收到异常标识。" << endl;
		return false;
		//It's not gonna happen or something seriously occured!!
	}
	return true;
}

/*
解析waitMessage
*/
void NetScene::getWaitMessage(const WaitMessageStruct &message) {
	myIndex = message.yourIndex;
	int playerIndex = message.playerIndex;
	Player *p = nullptr;
	if (playerIndex == myIndex){
		if (p1 == nullptr) {
			p1 = make_shared<Player>(Player());
		}
		p = p1.get();
	} else {
		if (p2 == nullptr) {
			p2 = make_shared<Player>(Player());
		}
		p = p2.get();
	}
	p->setColor((CHESS_COLOR)message.color);
	char name[16];
	memcpy(name, message.name, 16);
	p->setName(name);
	p->setConnected((uint32_t)message.connected);
	p->setRegret((uint32_t)message.regret);
	p->setDisconnected((uint32_t)message.disconnected);
	p->setRoomIndex((uint32_t)message.roomIndx);
	p->setPrepared((uint32_t)message.prepared);
}

/*
处理wait 的逻辑
*/
void NetScene::waitState() {
	cout << "现在是等待状态" << endl;
	recvPlayerMessage();
}

/*
处理start 的逻辑
*/
void NetScene::startState() {
	cout << "现在是开始状态" << endl;
	recvPlayerMessage();
}

/*
处理Run 的逻辑
*/
void NetScene::runState() {

}


/*
接收玩家1和玩家2的消息
*/
void NetScene::recvPlayerMessage() {
	WaitMessageStruct message;
	memcpy(&message, data, length);
	getWaitMessage(message);
	char name[16];
	memcpy(name, message.name, 16);
	cout << name;
	cout << " 本机编号：" << message.yourIndex;
	cout << " 当前包玩家颜色：" << message.color << " 当前包玩家索引：" << message.playerIndex;
	cout << " 当前包准备否 ：" << message.prepared << endl << endl;
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


/*线程函数
*/

int recvThread(void *data) {
	NetScene *netScene = (NetScene*)data;
	while (!netScene->threadQuit) {
		netScene->data = netScene->client.recvData(netScene->flag, netScene->length);
	}
	
	return 0;
}

void NetScene::initThread() {
	//创建并运行线程
	thread = SDL_CreateThread(recvThread, "recvThread", this);
}

void NetScene::releareThread() {
	threadQuit = true;
}
