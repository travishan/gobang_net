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
	bool addPlayer(const shared_ptr<Player> &player, uint16_t index);

	/*
	��ʼ������
	*/
	void initRoom();

	/*
	ִ����Ϸ�߼�
	*/
	virtual void frame() = 0;

	/*��ȡ���
	*/
	Player* getPlayer(uint16_t pi);
	Player* getAnotherPlayer(uint16_t pi);

	/*
	����
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
	��ʼ������
	*/
	void initBoard();

	/*
	����˫������ɫ
	*/
	void exchangeColor();

	/*
	��ʼ������������
	*/
	void initAttribute();

	/*
	��ʼ�����1 �� ���2
	*/
	void initP1(const shared_ptr<Player> &player, uint16_t index);
	void initP2(const shared_ptr<Player> &player, uint16_t index);

	/*
	������޵������
	*/
	void checkDisconnect();

	/*
	���¿�ʼ
	*/
	void restartInit();

protected:
	/*
	����wait ���߼�����Ⱦ
	*/
	virtual void waitState() = 0;
	virtual void waitStateRender() = 0;

	/*
	����start ���߼�����Ⱦ
	*/
	virtual void startState() = 0;
	virtual void startStateRender() = 0;

	/*
	����run ���߼�����Ⱦ
	*/
	virtual void runState() = 0;
	virtual void runStateRender() = 0;

	/*
	����end ���߼�
	*/
	virtual void endState() = 0;
	virtual void endStateRender() = 0;
protected:
	/*
	��ʼ��Texture����
	*/
	void loadAll();
	void loadBoardTexture(const string &);
	void loadChessTexture(const string &, const string &);

	/*
	render����
	*/
	void renderBoard();

	/*
	IO����
	*/
	bool checkMouseDown();

	/*
	�ж��������
	*/
	bool play();
protected:
	/*��Ҷ���
	*/
	shared_ptr<Player> p1, p2;

	/*�������
	*/
	uint16_t p1Index, p2Index;

	/*��������
	*/
	uint16_t roomIndex;

	/*����
	*/
	CHESS_COLOR chessBoard[GRID_NUM][GRID_NUM];

	/*��ǰ���ӷ�
	*/
	uint16_t currentPlayer;

	/*ʱ���ʱ
	*/
	uint16_t lastTime;

	/*��ǰ����
	*/
	uint16_t playerNum;

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
	shared_ptr<SDL_Texture> chessTextures[2];

	/*���̺����ӵ�Ŀ�����
	*/
	SDL_Rect distRect, chessRect;

	/*
	�������Ӧ���̸�
	*/
	uint16_t mouseRow, mouseCol;

	/*�ҵı��
	*/
	uint16_t myIndex;

	/*
	���ж���
	*/
	Referee referee;

	/*
	ʤ����
	*/
	uint16_t winner;
};






#endif // !__ROOM__H__
