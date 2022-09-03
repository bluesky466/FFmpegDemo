#include "sdl_window.h"

using namespace std;

SdlWindow* SdlWindow::sInstance = new SdlWindow();

SdlWindow* SdlWindow::GetInstance() {
    return sInstance;
}

SdlWindow::SdlWindow() : mWindow(NULL), mRenderer(NULL), mTexture(NULL) {
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_TIMER);
}

void SdlWindow::Show(const string& title, int width, int height) {
    mWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    if(!mWindow) {  
		printf("SDL: could not create window - exiting:%s\n", SDL_GetError());  
		return;
	}

    mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
    mTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, width, height);
    
    mRect.x = 0;
	mRect.y = 0;
	mRect.w = width;
	mRect.h = height;
}

bool SdlWindow::Update(uint8_t* YUVPlane[3], int YUVPitch[3]) {
    SDL_PollEvent(&mEvent);
    if(mEvent.type == SDL_QUIT) {
        return false;
    }

    SDL_UpdateYUVTexture(mTexture, &mRect,
            YUVPlane[0], YUVPitch[0],
            YUVPlane[1], YUVPitch[1],
            YUVPlane[2], YUVPitch[2]);

    SDL_RenderClear(mRenderer);  
    SDL_RenderCopy(mRenderer, mTexture,  NULL, &mRect);  
    SDL_RenderPresent(mRenderer);  
    SDL_Delay(40);
    return true;
}