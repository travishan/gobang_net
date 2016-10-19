#include "FrameManager.h"



void FrameManager::startUp() {



}

void FrameManager::shutDown() {

	delete FrameManager::get();
}

void FrameManager::frame() {
	auto sceneMgr = SceneManager::get();
	auto scene = sceneMgr->front();
	scene->logic();
}


