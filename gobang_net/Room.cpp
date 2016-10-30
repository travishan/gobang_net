#include "Room.h"

Room::Room() :
	p1(nullptr), p2(nullptr), p1Index(-1), p2Index(-1),
	currentPlayer(N), lastTime(0), playerNum(0),
	gameState(WAIT), lastTicks(0), boardTexture(nullptr){
	
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
	initBoard();
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
void Room::loadAll() {
	loadBoardTexture(BOARD_FILE);
	loadChessTexture(WHITE_FILE, BLACK_FILE);
}
void Room::loadBoardTexture(const string &file) {
	auto winMgr = WindowManager::get();
	boardTexture = shared_ptr<SDL_Texture>(winMgr->loadImage(file), SDL_DestroyTexture);
	distRect.x = 0;
	distRect.y = 0;
	SDL_QueryTexture(boardTexture.get(), nullptr, nullptr, &distRect.w, &distRect.h);
}

void Room::loadChessTexture(const string &w, const string &b) {
	auto winMgr = WindowManager::get();
	auto whiteChessTexture = shared_ptr<SDL_Texture>(winMgr->loadImage(w), SDL_DestroyTexture);
	auto blackChessTexture = shared_ptr<SDL_Texture>(winMgr->loadImage(b), SDL_DestroyTexture);
	chessTextures[0] = blackChessTexture;
	chessTextures[1] = whiteChessTexture;
	chessRect.x = chessRect.y = 0;
	chessRect.w = chessRect.h = 30;
}


/*
render函数
*/
void Room::renderBoard() {
	auto winMgr = WindowManager::get();
	winMgr->draw(boardTexture.get(), distRect);
	if (p1 != nullptr) {
		for (auto it = p1->begin(); it != p1->end(); ++it) {
			chessRect.y = it->row * GRID_WIDTH + F_X;
			chessRect.x = it->col * GRID_WIDTH + F_Y;
			winMgr->draw(chessTextures[p1->getColor()].get(), chessRect);
		}
	}
	if (p2 != nullptr) {
		for (auto it = p2->begin(); it != p2->end(); ++it) {
			chessRect.y = it->row * GRID_WIDTH + F_X;
			chessRect.x = it->col * GRID_WIDTH + F_Y;
			winMgr->draw(chessTextures[p2->getColor()].get(), chessRect);
		}
	}
	
}