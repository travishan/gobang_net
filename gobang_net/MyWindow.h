#pragma once

#include "define.h"


class MyWindow
{
public:
	MyWindow();
	~MyWindow();

public:
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
	unique_ptr<SDL_Window, void(*)(SDL_Window*)> m_Window
		= unique_ptr<SDL_Window, void(*)(SDL_Window*)>(nullptr, SDL_DestroyWindow);
	unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> m_Renderer
		= unique_ptr<SDL_Renderer,void(*)(SDL_Renderer*)>(nullptr, SDL_DestroyRenderer);
	//SDL_Window* m_Window;
	//SDL_Renderer* m_Renderer;
	SDL_Rect m_Box;
};

