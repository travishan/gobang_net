#ifndef __DEFINE__H__
#define __DEFINE__H__



#ifdef _WIN32
#include <Windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_thread.h>

#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_thread.h>

#endif // __WIN32


#include <string>
#include <memory>
#include <iostream>
#include <sstream>
#include <tchar.h>
#include <vector>
#include <time.h>
#include <functional>
#include <stack>



using namespace std;


#define WIN_WIDTH 535
#define WIN_HEIGHT 535


#define TTF_FILE "./res/simsun.ttc"
#define TTF_FILE2 "./res/simsun.ttc"

#define BOARD_FILE "./res/qipan.jpg"
#define WHITE_FILE "./res/white.png"
#define BLACK_FILE "./res/black.png"

#define BEGINSCENE_FILE "./res/beginScene.jpg"
#define BUTTON_NORMAL_FILE "./res/btn.png"
#define BUTTON_SELECTED_FILE "./res/btn1.png"
#define BUTTON_DISABLE_FILE "./res/btn2.png"
#define NUM_NORMAL_FILE "./res/num1.png"
#define NUM_SELECTED_FILE "./res/num2.png"

#define CALLBACK_0(__func__, __target__) bind(&__func__, __target__)

//边缘 22   490


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


#define PropertyBuilderByName(type, name, name2, domain)\
	domain:\
		type name;\
	public:\
		inline void set##name2(type v){\
			name = v;\
		}\
		inline type get##name2(){\
			return name;\
		}\

#define SingletonBuilder(className)\
public:\
	static className* get(){\
		static className  *m = nullptr;\
		if(m == nullptr){\
			m = new className();\
		}\
		return m;\
	}\

/*
黑白双方   0代表黑房 1代表白方
*/
typedef uint16_t CHESS_COLOR;
const uint16_t B = 0;
const uint16_t W = 1;
const uint16_t N = 2;

typedef struct B_POINT_Struct
{
	uint16_t row;
	uint16_t col;
}B_POINT;

typedef struct VALUE_POINT_Struct
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

/*
游戏状态  房间中的游戏状态
*/
typedef uint16_t GameState;
#define WAIT 0
#define START 1
#define RUN 2
#define REGRET 3
#define END 4


char* localeToUTF8(const char *src);






#endif // !__DEFINE__H__