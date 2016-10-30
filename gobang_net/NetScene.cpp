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
	recvData();
}


/*
���շ�������Ϣ
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
		cout << "����ҶϿ�����" << endl;

	}
	break;
	}
}

/*
�ж���Ϸ״̬
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
		cerr << "���󣺽��յ��쳣��ʶ��" << endl;
		return false;
		//It's not gonna happen or something seriously occured!!
	}
	return true;
}

/*
����waitMessage
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
����wait ���߼�
*/
void NetScene::waitState() {
	cout << "�����ǵȴ�״̬" << endl;
	recvPlayerMessage();
}

/*
����start ���߼�
*/
void NetScene::startState() {
	cout << "�����ǿ�ʼ״̬" << endl;
	recvPlayerMessage();
}

/*
����Run ���߼�
*/
void NetScene::runState() {

}


/*
�������1�����2����Ϣ
*/
void NetScene::recvPlayerMessage() {
	WaitMessageStruct message;
	memcpy(&message, data, length);
	getWaitMessage(message);
	char name[16];
	memcpy(name, message.name, 16);
	cout << name;
	cout << " ������ţ�" << message.yourIndex;
	cout << " ��ǰ�������ɫ��" << message.color << " ��ǰ�����������" << message.playerIndex;
	cout << " ��ǰ��׼���� ��" << message.prepared << endl << endl;
}







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


/*�̺߳���
*/

int recvThread(void *data) {
	NetScene *netScene = (NetScene*)data;
	while (!netScene->threadQuit) {
		netScene->data = netScene->client.recvData(netScene->flag, netScene->length);
	}
	
	return 0;
}

void NetScene::initThread() {
	//�����������߳�
	thread = SDL_CreateThread(recvThread, "recvThread", this);
}

void NetScene::releareThread() {
	threadQuit = true;
}
