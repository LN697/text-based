#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Renderer {
public:
    void init(const std::string& title, int width, int height);
    void render();
    void cleanup();
    
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;

    void renderText(const std::string& text, int x, int y);
};

#endif
