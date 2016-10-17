#include "FrameManager.h"



void FrameManager::startUp() {

	btnMgr = ButtonManager::get();
	IOMgr = IOManager::get();

	board = new Board();

	start = Button::create("./res/btn.png", "./res/btn1.png", "./res/btn2.png");
	start->setPosition(100, 200);
	start->addCallback(bind(&FrameManager::startCallback, this));
	btnMgr->addButton(start);

	end = Button::create("./res/btn.png", "./res/btn1.png", "./res/btn2.png");
	end->setPosition(200, 300);
	end->addCallback(bind(&FrameManager::endCallback, this));
	btnMgr->addButton(end);

}

void FrameManager::shutDown() {
	delete board;


	delete FrameManager::get();
}

void FrameManager::frame() {
	btnMgr->checkClick(IOMgr->getMouseLeftDown(),IOMgr->getMouseLeftUp());
	
}

void FrameManager::startCallback() {
	cout << "start!!!!!!!!!" << endl;
}

void FrameManager::endCallback() {
	cout << "end!!!!!!!!!" << endl;
}

