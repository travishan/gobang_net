#include "NetScene.h"




NetScene::NetScene(){
	Connector::connect(SERVER_IP, SERVER_PORT);
}

NetScene::~NetScene() {
	Connector::disconnect();
}

/*
�߼�������  virtual
*/
void NetScene::logic() {
	
}

/*
��Ⱦ������ virtual
*/
void NetScene::render() {

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
	data = Connector::client.recvData(flag, length);
	checkGameState();
	switch (gameState) {
	case WAIT:
		waitState();
		break;
	case START:
		startState();
		break;
	case RUN:
	{

	}
	break;
	case REGRET:
	{

	}
	break;
	case END:
	{
		//cout << "����ҶϿ�����" << endl;

	}
	break;
	}
}

/*
�ж���Ϸ״̬
*/
void NetScene::checkGameState() {
	if (flag == FLAG_WAIT || FLAG_FULL) {
		gameState = WAIT;
	} else if (flag == FLAG_START) {
		gameState = START;
	} else if (flag == FLAG_RUN || FLAG_CHANGE) {
		gameState = RUN;
	} else if (flag == (FLAG_QUERY_REGRET || FLAG_REGRETED)) {
		gameState = REGRET;
	}else if (flag == FLAG_END) {
		gameState = END;
	} else {
		//It's not gonna happen or something seriously occured!!
	}
}

/*
����wait ���߼�
*/
void NetScene::waitState() {

}

/*
����start ���߼�
*/
void NetScene::startState() {

}

/*
����Run ���߼�
*/
void NetScene::runState() {

}


/*
�ӷ�������������
*/
void NetScene::recvData() {

}










/***********************

��ʼ������

************************/


