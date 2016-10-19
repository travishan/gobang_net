#include "RenderManager.h"



void RenderManager::startUp() {
	winMgr = WindowManager::get();
	try {
		winMgr->init("gobang");
	} catch (const runtime_error &e) {
		cout << e.what() << endl;
		winMgr->quit();
		return;
	}
}

void RenderManager::shutDown() {
	winMgr->quit();
	delete RenderManager::get();
}

void RenderManager::rendEverything(const GameState &state){
	winMgr->clear();

	//if (state == Select) {
	//	
	//}
	auto sceneMgr = SceneManager::get();
	auto scene = sceneMgr->front();
	scene->render();



	winMgr->present();
}