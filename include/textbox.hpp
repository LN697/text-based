#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

class TextBox {
public:
    TextBox(SDL_Renderer* renderer, TTF_Font* font, const SDL_Rect& rect, const std::string& text, int cps = 15);

    void update(Uint32 deltaTime);
    void render();

    void setText(const std::string& newText);
    bool isDone() const;

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Rect rect;
    std::string fullText;
    std::vector<std::string> wrappedLines;
    int charsPerSecond;
    Uint32 elapsedTime;
    int visibleChars;

    void wrapText();
};
