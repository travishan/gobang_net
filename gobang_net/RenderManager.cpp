#include "RenderManager.h"



RenderManager::RenderManager()
	:winRender(new MyWindow())
{

}


void RenderManager::rendEverything() {
	winRender->clear();


	winRender->present();
}