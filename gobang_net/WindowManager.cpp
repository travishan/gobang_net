#include "WindowManager.h"





void WindowManager::startUp() {


}


void WindowManager::shutDown() {

}

void WindowManager::init(string title) {
	//Initialize all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		throw runtime_error("SDL Init Failed");
	}
	if (TTF_Init() == -1) {
		throw runtime_error("TTF Init Failed");
	}
	

	//Setup our window size
	winBox.x = 0;
	winBox.y = 0;
	winBox.w = WIN_WIDTH;
	winBox.h = WIN_HEIGHT;

	//Create our window
	window.reset(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winBox.w, winBox.h, SDL_WINDOW_SHOWN));
	//Make sure it created ok
	if (window == nullptr) {
		throw runtime_error("Failed to create window");
	}

	//Create our renderer
	renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
	//Make sure it created ok
	if (renderer == nullptr) {
		throw runtime_error("Failed to create renderer");
	}
}



void WindowManager::quit() {
	TTF_Quit();
	SDL_Quit();
}


void WindowManager::draw(int x, int y, SDL_Texture *tex) {
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);

	SDL_RenderCopy(renderer.get(), tex, NULL, &pos);
}

void WindowManager::draw(SDL_Texture* tex, SDL_Rect &dstRect, SDL_Rect *clip, float angle, int xPivot, int yPivot, SDL_RendererFlip flip) {
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
	SDL_RenderCopyEx(renderer.get(), tex, clip, &dstRect, angle, &pivot, flip);

}



SDL_Texture* WindowManager::loadImage(string file) {
	SDL_Texture* tex = nullptr;
	tex = IMG_LoadTexture(renderer.get(), file.c_str());
	if (tex == nullptr)
		throw std::runtime_error("Failed to load image: " + file + IMG_GetError());
	return tex;
}

extern char* localeToUTF8(char *src);

SDL_Texture* WindowManager::renderText(string message, string fontFile, SDL_Color color, int fontSize) {
	//Open the font
	TTF_Font *font = nullptr;
	font = TTF_OpenFont(fontFile.c_str(), fontSize);
	if (font == nullptr)
		throw std::runtime_error("Failed to load font: " + fontFile + TTF_GetError());


	//Render the message to an SDL_Surface, as that's what TTF_RenderText_X returns
	//SDL_Surface *surf = TTF_RenderUNICODE_Solid(font, cstringToUnicode(message.c_str()), color);
	//SDL_Surface *surf = TTF_RenderUTF8_Blended(font, message.c_str(), color);
	SDL_Surface *surf = TTF_RenderUTF8_Blended(font, localeToUTF8(message.c_str()), color);

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer.get(), surf);
	//Clean up unneeded stuff
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);

	return texture;
}


void WindowManager::clear() {
	SDL_RenderClear(renderer.get());
}


void WindowManager::present() {
	SDL_RenderPresent(renderer.get());
}


SDL_Rect WindowManager::box() {
	//Update mBox to match the current window size
	SDL_GetWindowSize(window.get(), &winBox.w, &winBox.h);
	return winBox;
}