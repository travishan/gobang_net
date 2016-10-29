#include "Room.h"

Room::Room() :
	p1(nullptr), p2(nullptr), p1Index(-1), p2Index(-1),
	currentPlayer(N), lastTime(0), playerNum(0),
	gameState(WAIT), lastTicks(0), boardTexture(nullptr),
	whiteChessTexture(nullptr), blackChessTexture(nullptr){
	
}

Room::~Room() {}

void Room::initP1(const shared_ptr<Player> &player, int index) {
	p1 = player;
	p1Index = index;
	p1->setColor(B);
}
void Room::initP2(const shared_ptr<Player> &player, int index) {
	p2 = player;
	p2Index = index;
	p2->setColor(W);
}

bool Room::addPlayer(const shared_ptr<Player> &player, int index) {
	if (playerNum == 0) {
		initP1(player, index);
	} else if (playerNum == 1) {
		initP2(player, index);
	} else {
		return false;
	}
	++playerNum;
	return true;
}

void Room::initBoard() {
	fillMatrix(chessBoard, N);
}

void Room::initAttribute() {
	currentPlayer = N;
	lastTime = PLAYTIME;
}

void Room::initRoom() {
	initRoom();
	initAttribute();
}


/*
检查有无掉线玩家
*/
void Room::checkDisconnect() {
	if ((p1 != nullptr && p1->isDisconnected()) || (p2 != nullptr && p2->isDisconnected())) {
		gameState = END;
	}
}

/*
初始化Texture函数
*/
void Room::loadBoardTexture(const string &file) {
	auto winMgr = WindowManager::get();
	boardTexture = shared_ptr<SDL_Texture>(winMgr->loadImage(file), SDL_DestroyTexture);
	distRect.x = 0;
	distRect.y = 0;
	SDL_QueryTexture(boardTexture.get(), nullptr, nullptr, &distRect.w, &distRect.h);
}

void Room::loadChessTexture(const string &w, const string &b) {
	auto winMgr = WindowManager::get();
	whiteChessTexture = shared_ptr<SDL_Texture>(winMgr->loadImage(w), SDL_DestroyTexture);
	blackChessTexture = shared_ptr<SDL_Texture>(winMgr->loadImage(b), SDL_DestroyTexture);
	chessRect.x = chessRect.y = 0;
	chessRect.w = chessRect.h = 30;
}