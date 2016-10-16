#include "RenderManager.h"



RenderManager::RenderManager(){}


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
}

void RenderManager::rendEverything() {
	winRender->clear();

	winRender->present();
}