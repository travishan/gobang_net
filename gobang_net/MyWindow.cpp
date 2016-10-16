#include "MyWindow.h"


MyWindow::MyWindow()
{
}


MyWindow::~MyWindow()
{
}


void MyWindow::init(string title)
{
	//Initialize all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
		throw runtime_error("SDL Init Failed");
	}
	if (TTF_Init() == -1){
		throw runtime_error("TTF Init Failed");
	}

	//Setup our window size
	m_Box.x = 0;
	m_Box.y = 0;
	m_Box.w = WIN_WIDTH;
	m_Box.h = WIN_HEIGHT;

	//Create our window
	m_Window.reset(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Box.w, m_Box.h, SDL_WINDOW_SHOWN));
	//Make sure it created ok
	if (m_Window == nullptr){
		throw runtime_error("Failed to create window");
	}

	//Create our renderer
	m_Renderer.reset(SDL_CreateRenderer(m_Window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
	//Make sure it created ok
	if(m_Renderer == nullptr){
		throw runtime_error("Failed to create renderer");
	}
}



void MyWindow::quit()
{
	TTF_Quit();
	SDL_Quit();
}


void MyWindow::draw(int x, int y, SDL_Texture *tex) {
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);

	SDL_RenderCopy(m_Renderer.get(), tex, NULL, &pos);
}

void MyWindow::draw(SDL_Texture* tex, SDL_Rect &dstRect, SDL_Rect *clip, float angle, int xPivot, int yPivot, SDL_RendererFlip flip)
{
	//Convert pivot pos from relative to object's center to screen space
	xPivot += dstRect.w / 2;
	yPivot += dstRect.h / 2;
	//SDL expects an SDL_Point as the pivot location
	SDL_Point pivot = { xPivot, yPivot };
	//Draw the texture
	/*if (clip != nullptr){
		dstRect.w = clip->w;
		dstRect.h = clip->h;
	}
	else{
		SDL_QueryTexture(tex, nullptr, nullptr, &dstRect.w, &dstRect.h);
	}*/
	SDL_RenderCopyEx(m_Renderer.get(), tex, clip, &dstRect, angle, &pivot, flip);
	
}



SDL_Texture* MyWindow::loadImage(string file)
{
	SDL_Texture* tex = nullptr;
	tex = IMG_LoadTexture(m_Renderer.get(), file.c_str());
	if (tex == nullptr)
		throw std::runtime_error("Failed to load image: " + file + IMG_GetError());
	return tex;
}

SDL_Texture* MyWindow::renderText(string message, string fontFile, SDL_Color color, int fontSize)
{
	//Open the font
	TTF_Font *font = nullptr;
	font = TTF_OpenFont(fontFile.c_str(), fontSize);
	if (font == nullptr)
		throw std::runtime_error("Failed to load font: " + fontFile + TTF_GetError());

	
	//Render the message to an SDL_Surface, as that's what TTF_RenderText_X returns
	//SDL_Surface *surf = TTF_RenderUNICODE_Solid(font, cstringToUnicode(message.c_str()), color);
	SDL_Surface *surf = TTF_RenderUTF8_Blended(font, message.c_str(), color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(m_Renderer.get(), surf);
	//Clean up unneeded stuff
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);

	return texture;
}


void MyWindow::clear()
{
	SDL_RenderClear(m_Renderer.get());
}


void MyWindow::present()
{
	SDL_RenderPresent(m_Renderer.get());
}


SDL_Rect MyWindow::box()
{
	//Update mBox to match the current window size
	SDL_GetWindowSize(m_Window.get(), &m_Box.w, &m_Box.h);
	return m_Box;
}