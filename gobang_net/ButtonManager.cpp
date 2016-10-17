#include "ButtonManager.h"




void Button::init(const string &normalImage, const string &selectedImage, const string &disableImage) {
	auto winMgr = WindowManager::get();
	
	try {
		normalTex = winMgr->loadImage(normalImage);
	} catch (const runtime_error &e) {
		cout << e.what() << endl;
	}
	try {
		selectedTex = winMgr->loadImage(selectedImage);
	} catch (const runtime_error &e) {
		cout << e.what() << endl;
	}
	try {
		disableTex = winMgr->loadImage(disableImage);
	} catch (const runtime_error &e) {
		cout << e.what() << endl;
	}
}


void Button::addToBtnMgr() {

}








void ButtonManager::startUp() {



}


void ButtonManager::shutDown() {


}

