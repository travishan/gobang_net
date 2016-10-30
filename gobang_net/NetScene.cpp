#include "NetScene.h"




NetScene::NetScene() : myIndex(-1), prepareBtn(nullptr), thread(nullptr), threadQuit(false){
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
�߼�������  virtual
*/
void NetScene::logic() {
	frame();
	checkButtonClick();
}

/*
��Ⱦ������ virtual
*/
void NetScene::render() {
	Room::renderBoard();
	btnCollection->render();
}


/*
ִ����Ϸ�߼�
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
		cout << "��Ϸ����" << endl;
	}
		break;
	}
}


/*
�ж���Ϸ״̬
*/
//bool NetScene::checkGameState() {
//	if (flag == FLAG_WAIT || flag == FLAG_FULL) {
//		gameState = WAIT;
//	} else if (flag == FLAG_START) {
//		gameState = START;
//	} else if (flag == FLAG_RUN || flag == FLAG_CHANGE) {
//		gameState = RUN;
//	} else if (flag == FLAG_QUERY_REGRET || flag == FLAG_REGRETED) {
//		gameState = REGRET;
//	}else if (flag == FLAG_END) {
//		gameState = END;
//	} else {
//		cerr << "���󣺽��յ��쳣��ʶ��" << endl;
//		return false;
//		//It's not gonna happen or something seriously occured!!
//	}
//	return true;
//}

/*
����GameMessage
*/
void NetScene::setGameMessage(const Game_Message &message) {
	gameState = (GameState)message.gameState;
	p1Index = message.p1Index;
	p2Index = message.p2Index;
	currentPlayer = message.curSide;
	playerNum = message.playerNum;
	lastTime = message.time;
}

/*
����waitMessage
*/
void NetScene::setPlayerMessage(const Player_Message &message) {
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
����wait ���߼�
*/
void NetScene::waitState() {
	cout << "�����ǵȴ�״̬" << endl;
	cout << "current player number : " << playerNum;
	cout << "p1Index : " << p1Index << ", p2Index :" << p2Index << endl << endl;
}

/*
����start ���߼�
*/
void NetScene::startState() {
	cout << "�����ǿ�ʼ״̬" << endl;
}

/*
����Run ���߼�
*/
void NetScene::runState() {

}

/*
�������1�����2����Ϣ
*/
//void NetScene::recvPlayerMessage() {
//	Player_Message message;
//	memcpy(&message, data, length);
//	getWaitMessage(message);
//	char name[16];
//	memcpy(name, message.name, 16);
//	cout << name;
//	cout << " ������ţ�" << message.yourIndex;
//	cout << " ��ǰ�������ɫ��" << message.color << " ��ǰ�����������" << message.playerIndex;
//	cout << " ��ǰ��׼���� ��" << message.prepared << endl << endl;
//}


/***********************

��ʼ������

************************/


/*
��ʼ��button
*/
void NetScene::initButton() {
	prepareBtn = Button::create(BUTTON_NORMAL_FILE, BUTTON_SELECTED_FILE, BUTTON_DISABLE_FILE);
	prepareBtn->setPosition(210, 380);
	prepareBtn->setTitle("׼��", SDL_Color{ 0, 0, 0 }, 20);
	prepareBtn->setCallback(CALLBACK_0(NetScene::prepareBtnCallBack, this));
	this->addButton(prepareBtn);
}


/*
�ص�����
*/
void NetScene::prepareBtnCallBack() {
	FlagType flag = FLAG_READY;
	client.sendData(nullptr, 0, flag);
	prepareBtn->setDisabled(true);
}


/*
�̺߳���  ������մӷ�������������Ϣ�������н���
GameMessage ��ǰ��Ϸ�����Ϣ
PlayerMessage ��ǰ��������Ϣ
PlayMessage ���巽�����Ϣ
RegretMessage ���������Ϣ
*/

int recvThread(void *data) {
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
		}break;
		case FLAG_PLAYER_INFO:
		{
			Player_Message msg;
			memcpy(&msg, recvData, length);
			netScene->setPlayerMessage(msg);
		}break;
		case FLAG_PLAY_INFO:
			break;
		case FLAG_QUERY_REGRET:
			break;
		}
	}
	return 0;
}

void NetScene::initThread() {
	//�����������߳�
	thread = SDL_CreateThread(recvThread, "recvThread", this);
}

void NetScene::releaseThread() {
	threadQuit = true;
	//SDL_LASTERROR
}
