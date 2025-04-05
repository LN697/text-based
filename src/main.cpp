#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "textbox.hpp"
#include "parameters.hpp"

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("TextBox Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                            SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font* font = TTF_OpenFont("assets/fonts/arial.ttf", 24);
    if (!font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return 1;
    }

    SDL_Rect textRect = {TEXTBOX_OFFSET_X, TEXTBOX_OFFSET_Y, TEXTBOX_HEIGHT, TEXTBOX_WIDTH};
    TextBox textBox(renderer, font, textRect,
        "This is a long line of dialogue that will be wrapped properly and shown with a typewriter effect.", 30);

    bool running = true;
    Uint32 lastTime = SDL_GetTicks();

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }

        Uint32 currentTime = SDL_GetTicks();
        Uint32 deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        textBox.update(deltaTime);

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        textBox.render();

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
