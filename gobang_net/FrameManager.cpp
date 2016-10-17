#include "FrameManager.h"



void FrameManager::startUp() {
	board = new Board();
}

void FrameManager::shutDown() {
	delete board;


	delete FrameManager::get();
}

void FrameManager::frame() {

}

