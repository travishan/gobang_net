#pragma once
#ifndef __DEFINE__H__
#define __DEFINE__H__




#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <memory>
#include <iostream>
#include <sstream>
#include <tchar.h>
#include <Windows.h>
#include <vector>
#include <time.h>



using namespace std;


#define WIN_WIDTH 535
#define WIN_HEIGHT 535


#define TTF_FILE "./res/arial.ttf"
#define TTF_FILE2 "./res/simsun.ttc"

#define BOARD_FILE "./res/qipan.jpg"
#define WHITE_FILE "./res/white.png"
#define BLACK_FILE "./res/black.png"


//��Ե 22   490


#define F_X 8
#define F_Y 8

#define GRID_MIN 0
#define GRID_NUM 15
#define GRID_COUNT 15*15

#define GRID_WIDTH 35
// 35 * 14 = 525
#define LEFT_BOUND 0
#define RIGHT_BOUND 518
#define TOP_BOUND 0
#define BOTTOM_BOUND 518

enum CHESS_COLOR
{
	B = 0,
	W,
	N
};

typedef struct B_POINT
{
	int row;
	int col;
}B_POINT;

typedef struct VALUE_POINT
{
	B_POINT pos;
	int value;
}VALUE_POINT;

enum DIR
{
	HROZION = 0,
	VERTICAL,
	LEFT,
	RIGHT,
};
enum GameState
{
	Select = 0,
	Single,
	Network,
	Ending
};

inline
void fillMatrix(int(&a)[15][15][8][2], int n) {
	memset(a, n, sizeof(a));
}

inline
void fillMatrix(int(&a)[15][15], int n) {
	memset(a, n, sizeof(a));
}

inline
void fillMatrix(CHESS_COLOR(&a)[15][15], int n) {
	memset(a, n, sizeof(a));
}



#endif // !__DEFINE__H__