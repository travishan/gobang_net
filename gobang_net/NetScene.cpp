#include "NetScene.h"




NetScene::NetScene(){
	Connector::connect(SERVER_IP, SERVER_PORT);
}

NetScene::~NetScene() {
	Connector::disconnect();
}

/*
逻辑处理函数  virtual
*/
void NetScene::logic() {
	
}

/*
渲染处理函数 virtual
*/
void NetScene::render() {

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
		//cout << "有玩家断开连接" << endl;

	}
	break;
	}
}

/*
判断游戏状态
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
处理wait 的逻辑
*/
void NetScene::waitState() {

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

}


/*
从服务器接收数据
*/
void NetScene::recvData() {

}










/***********************

初始化函数

************************/


