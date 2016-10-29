#ifndef __ROOM__H__
#define __ROOM__H__


#include "define.h"
#include "Player.h"
#include "Referee.h"
#include "WindowManager.h"

#define PLAYTIME 30

/***************************

Room��
����ÿһ�����ڶ�ս�������Ϣ����ǰ������Ϣ�� �Լ�ӵ�в����࣬�����жϾ��ơ�


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
	��ʼ�����1,2
	*/
	bool addPlayer(const shared_ptr<Player> &player, int index);

	/*
	��ʼ������
	*/
	void initRoom();

	/*
	ִ����Ϸ�߼�
	*/
	virtual void frame() = 0;

	/*
	get set
	*/
	int getPlayerNum() { return playerNum; }
	void setGameState(GameState state) { gameState = state; }
	GameState getGameState() { return gameState; }
protected:
	/*
	��ʼ������
	*/
	void initBoard();

	/*
	��ʼ������������
	*/
	void initAttribute();

	/*
	��ʼ�����1 �� ���2
	*/
	void initP1(const shared_ptr<Player> &player, int index);
	void initP2(const shared_ptr<Player> &player, int index);

	/*
	������޵������
	*/
	void checkDisconnect();
protected:
	/*
	����wait ���߼�
	*/
	virtual void waitState() = 0;

	/*
	����start ���߼�
	*/
	virtual void startState() = 0;

	/*
	����run ���߼�
	*/
	virtual void runState() = 0;

protected:
	/*
	��ʼ��Texture����
	*/
	void loadBoardTexture(const string &);
	void loadChessTexture(const string &, const string &);

protected:
	/*��Ҷ���
	*/
	shared_ptr<Player> p1, p2;

	/*�������
	*/
	int p1Index, p2Index;

	/*����
	*/
	CHESS_COLOR chessBoard[GRID_NUM][GRID_NUM];

	/*��ǰ���ӷ�
	*/
	CHESS_COLOR currentPlayer;

	/*ʱ���ʱ
	*/
	int lastTime;

	/*��ǰ����
	*/
	int playerNum;

	/*��Ϸ״̬
	*/
	GameState gameState;

	/*
	ʱ���
	*/
	uint32_t lastTicks;

	/*������Ҫ���Ƶ�Texture
	*/
	shared_ptr<SDL_Texture> boardTexture;
	shared_ptr<SDL_Texture> whiteChessTexture;
	shared_ptr<SDL_Texture> blackChessTexture;

	/*���̺����ӵ�Ŀ�����
	*/
	SDL_Rect distRect, chessRect;
};






#endif // !__ROOM__H__
