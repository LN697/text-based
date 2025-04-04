#include "game.hpp"
#include <iostream>

Game::Game() : running(true) {}

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() == -1) {
        std::cerr << "SDL Initialization Failed: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer.init("Text-Based Game", 640, 480);
    return true;
}

void Game::run() {
    if (!init()) return;

    while (running) {
        inputHandler.handleEvents(running);
        renderer.render();
    }

    cleanup();
}

void Game::cleanup() {
    renderer.cleanup();
    TTF_Quit();
    SDL_Quit();
}
