#ifndef __ROOM__H__
#define __ROOM__H__


#include "define.h"
#include "MathDefine.h"
#include "Player.h"
#include "Referee.h"
#include "WindowManager.h"
#include "IOManager.h"

#define PLAYTIME 30

/***************************

Room类
保存每一对正在对战的玩家信息，当前局面信息， 以及拥有裁判类，用于判断局势。


****************************/
class Room
{
	friend class Referee;
protected:
	typedef function<void(int, uint8_t*, uint16_t, uint16_t)> SEND_FUN;
public:
	Room();
	~Room();

	/*
	初始化玩家1,2
	*/
	bool addPlayer(const shared_ptr<Player> &player, uint16_t index);

	/*
	初始化房间
	*/
	void initRoom();

	/*
	执行游戏逻辑
	*/
	virtual void frame() = 0;

	/*获取玩家
	*/
	Player* getPlayer(uint16_t pi);
	Player* getAnotherPlayer(uint16_t pi);

	/*
	换边
	*/
	void changeSide();

	/*
	get set
	*/
	uint16_t getPlayerNum() { return playerNum; }
	void setGameState(GameState state) { gameState = state; }
	GameState getGameState() { return gameState; }
	void setRoomIndex(uint16_t index) { roomIndex = index; }
	uint16_t getRoomIndex() { return roomIndex; }
	void setWinner(uint16_t player) { winner = player; }
	uint16_t getWinner() { return winner; }

protected:
	/*
	初始化棋盘
	*/
	void initBoard();

	/*
	交换双方的颜色
	*/
	void exchangeColor();

	/*
	初始化棋局相关属性
	*/
	void initAttribute();

	/*
	初始化玩家1 和 玩家2
	*/
	void initP1(const shared_ptr<Player> &player, uint16_t index);
	void initP2(const shared_ptr<Player> &player, uint16_t index);

	/*
	检查有无掉线玩家
	*/
	void checkDisconnect();

	/*
	重新开始
	*/
	void restartInit();

protected:
	/*
	处理wait 的逻辑和渲染
	*/
	virtual void waitState() = 0;
	virtual void waitStateRender() = 0;

	/*
	处理start 的逻辑和渲染
	*/
	virtual void startState() = 0;
	virtual void startStateRender() = 0;

	/*
	处理run 的逻辑和渲染
	*/
	virtual void runState() = 0;
	virtual void runStateRender() = 0;

	/*
	处理end 的逻辑
	*/
	virtual void endState() = 0;
	virtual void endStateRender() = 0;
protected:
	/*
	初始化Texture函数
	*/
	void loadAll();
	void loadBoardTexture(const string &);
	void loadChessTexture(const string &, const string &);

	/*
	render函数
	*/
	void renderBoard();

	/*
	IO交互
	*/
	bool checkMouseDown();

	/*
	判断玩家走棋
	*/
	bool play();
protected:
	/*玩家对象
	*/
	shared_ptr<Player> p1, p2;

	/*玩家索引
	*/
	uint16_t p1Index, p2Index;

	/*房间索引
	*/
	uint16_t roomIndex;

	/*棋盘
	*/
	CHESS_COLOR chessBoard[GRID_NUM][GRID_NUM];

	/*当前下子方
	*/
	uint16_t currentPlayer;

	/*时间计时
	*/
	uint16_t lastTime;

	/*当前人数
	*/
	uint16_t playerNum;

	/*游戏状态
	*/
	GameState gameState;

	/*
	时间戳
	*/
	uint32_t lastTicks;

	/*所有需要绘制的Texture
	*/
	shared_ptr<SDL_Texture> boardTexture;
	shared_ptr<SDL_Texture> chessTextures[2];

	/*棋盘和棋子的目标矩形
	*/
	SDL_Rect distRect, chessRect;

	/*
	鼠标点击对应棋盘格
	*/
	uint16_t mouseRow, mouseCol;

	/*我的编号
	*/
	uint16_t myIndex;

	/*
	裁判对象
	*/
	Referee referee;

	/*
	胜利方
	*/
	uint16_t winner;
};






#endif // !__ROOM__H__
