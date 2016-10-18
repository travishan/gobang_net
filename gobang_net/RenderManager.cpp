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
	btnMgr = ButtonManager::get();
}

void RenderManager::shutDown() {
	winMgr->quit();
	delete RenderManager::get();
}

void RenderManager::rendEverything(const GameState &state){
	winMgr->clear();

	if (state == Select) {
		auto scene = BeginScene::get();
		scene->render();
		btnMgr->render();
	}
	



	winMgr->present();
}