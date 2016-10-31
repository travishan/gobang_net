#include "Room.h"

Room::Room() :
	p1(nullptr), p2(nullptr), p1Index(-1), p2Index(-1), roomIndex(-1),
	currentPlayer(N), lastTime(0), playerNum(0),
	gameState(WAIT), lastTicks(0), boardTexture(nullptr),
	mouseRow(0), mouseCol(0), myIndex(-1) {
	initRoom();
}

Room::~Room() {}

void Room::initP1(const shared_ptr<Player> &player, uint16_t index) {
	p1 = player;
	p1Index = index;
	p1->setColor(B);
}
void Room::initP2(const shared_ptr<Player> &player, uint16_t index) {
	p2 = player;
	p2Index = index;
	p2->setColor(W);
}

bool Room::addPlayer(const shared_ptr<Player> &player, uint16_t index) {
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

/*
换边
*/
void Room::changeSide() {
	if (currentPlayer == p1Index) {
		currentPlayer = p2Index;
	} else {
		currentPlayer = p1Index;
	}
}

/*获取玩家
*/
Player* Room::getPlayer(uint16_t pi) {
	Player *p = nullptr;
	if (pi == p1Index)
		p = p1.get();
	else
		p = p2.get();
	return p;
}
Player* Room::getAnotherPlayer(uint16_t pi) {
	Player *p = nullptr;
	if (pi == p1Index)
		p = p2.get();
	else if (pi == p2Index)
		p = p1.get();
	else
		return nullptr;
	return p;
}


/*
IO交互
*/
bool Room::checkMouseDown() {
	int x, y;
	SDL_GetMouseState(&x, &y);
	x -= F_X;
	y -= F_Y;
	if (x < LEFT_BOUND || y < TOP_BOUND
		|| x > RIGHT_BOUND || y > BOTTOM_BOUND) {
		return false;
	}
	mouseCol = (uint16_t)x / GRID_WIDTH;
	mouseRow = (uint16_t)y / GRID_WIDTH;
	return true;
}

/*
判断玩家走棋
*/
bool Room::play() {
	
	if (gameState == RUN &&currentPlayer == myIndex) {
		auto ioMgr = IOManager::get();
		if (ioMgr->getMouseLeftUp()) {
			ioMgr->setMouseLeftUp(false);
			auto p = getPlayer(myIndex);
			if (p == nullptr) return false;
			auto color = p->getColor();
			if (checkMouseDown()) {
				if (chessBoard[mouseRow][mouseCol] == N) {
					chessBoard[mouseRow][mouseCol] = color;
					p->push_back(B_POINT{ mouseRow,mouseCol });
					return true;
				}
			}
		}
	}
	return false;
}