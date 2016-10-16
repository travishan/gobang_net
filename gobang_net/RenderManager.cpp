#include "RenderManager.h"



void RenderManager::startUp() {
	winRender = make_shared<MyWindow>();
	try {
		winRender->init("gobang");
	} catch (const runtime_error &e) {
		cout << e.what() << endl;
		winRender->quit();
		return;
	}
}

void RenderManager::shutDown() {
	winRender->quit();
	delete RenderManager::get();
}

void RenderManager::rendEverything() {
	winRender->clear();

	winRender->present();
}