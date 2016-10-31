#ifndef __MATHDEFINE__H__
#define __MATHDEFINE__H__


#include "define.h"

inline
void fillMatrix(int(&a)[15][15][8][2], int n) {
	memset(a, n, sizeof(a));
}

inline
void fillMatrix(int(&a)[15][15], int n) {
	memset(a, n, sizeof(a));
}

inline
void fillMatrix(CHESS_COLOR(&a)[15][15], uint16_t n) {
	//memset(a, 514, sizeof(a));
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 15; ++j) {
			a[i][j] = n;
		}
	}
}





#endif // !__MATHDEFINE__H__

