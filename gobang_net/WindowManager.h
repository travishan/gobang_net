#ifndef __WINDOWMANAGER__H__
#define __WINDOWMANAGER__H__

#include "Manager.h"

class WindowManager : public Manager
{
	SingletonBuilder(WindowManager)
public:
	virtual void startUp();
	virtual void shutDown();

	void init(string title = "window");
	void quit();
	void draw(int x, int y, SDL_Texture *tex);
	void draw(SDL_Texture* tex, SDL_Rect &dstRect, SDL_Rect *clip = nullptr, float angle = 0.0, int xPivot = 0, int yPivot = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
	SDL_Texture* loadImage(string file);
	SDL_Texture* renderText(string message, string fontFile, SDL_Color color, int fontSize);
	void clear();
	void present();
	SDL_Rect box();
private:
	unique_ptr<SDL_Window, void(*)(SDL_Window*)> window
		= unique_ptr<SDL_Window, void(*)(SDL_Window*)>(nullptr, SDL_DestroyWindow);
	unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> renderer
		= unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)>(nullptr, SDL_DestroyRenderer);


	SDL_Rect winBox;

};






























#endif // !__WINDOWMANAGER__H__
