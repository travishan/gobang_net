#include "SceneManager.h"


/**************************

Scene

**************************/


void Scene::addButton(Button *btn) {
	btnCollection->addButton(btn);
}


void Scene::checkButtonClick() {
	auto ioMgr = IOManager::get();
	btnCollection->checkClick(ioMgr->getMouseLeftDown(), ioMgr->getMouseLeftUp());
}

/**************************

SceneManager

**************************/



void SceneManager::startUp() {

}


void SceneManager::shutDown() {
	delete get();
}

void SceneManager::push(Scene* scene) {
	sceneStack.push(scene);
}


Scene* SceneManager::front() {
	return sceneStack.top();
}