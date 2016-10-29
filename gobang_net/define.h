#ifndef __DEFINE__H__
#define __DEFINE__H__

#ifdef _WIN32
#include <SDL.h>
#include <SDL_net.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#endif // __WIN32


#include <string>
#include <memory>
#include <iostream>
#include <sstream>
#include <tchar.h>
#include <Windows.h>
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


/*
客户端向服务器发送的消息头   uint16_t类型
*/
#define FLAG_PLAY 0x0011				//下棋
#define FLAG_ASK_REGRET 0x0012	//请求悔棋
#define FLAG_RETURN_REGRET 0x0013  //另一方返回是否同意悔棋
#define FLAG_READY 0x0014   //客户端准备好开始游戏

/*
服务端向客户端发送的消息头  uint16_t类型
*/
#define FLAG_WAIT 0x0021				//等待另一个玩家
#define FLAG_START 0x0022				//开始游戏
#define FLAG_RUN 0x0023					//等待
#define FLAG_CHANGE 0x0024			//换边
#define FLAG_QUERY_REGRET 0x0025//询问另一个
#define FLAG_REGRETED 0x0026		//悔棋
#define FLAG_FULL 0x0027					//所有房间都满了
#define FLAG_END 0x0028					//游戏结束


typedef uint16_t FlagType;
typedef uint16_t LengthType;
typedef uint8_t* DataType;

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

enum CHESS_COLOR
{
	B = 0,
	W,
	N
};

typedef struct
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

/*
游戏状态  房间中的游戏状态
*/
enum GameState
{
	WAIT = 0,
	START,
	RUN,
	REGRET,
	END
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

char* localeToUTF8(const char *src);

#endif // !__DEFINE__H__