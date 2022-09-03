#include <string>

extern "C" {
#include <SDL2/SDL.h>
}

class SdlWindow {
public:
    static SdlWindow* GetInstance();

    void Show(const std::string& title, int width, int height);
    bool Update(uint8_t* YUVPlane[3], int YUVPitch[3]);

private:
    SdlWindow();

    static SdlWindow* sInstance;

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    SDL_Texture*  mTexture;
    SDL_Rect  mRect;
    SDL_Event mEvent;
};