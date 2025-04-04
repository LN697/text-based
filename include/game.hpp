#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "renderer.hpp"
#include "handler.hpp"

class Game {
public:
    Game();
    void run();

private:
    bool running;
    Renderer renderer;
    InputHandler inputHandler;

    bool init();
    void cleanup();
};

#endif
