#include "textbox.hpp"
#include <sstream>

TextBox::TextBox(SDL_Renderer* r, TTF_Font* f, const SDL_Rect& box, const std::string& text, int cps)
    : renderer(r), font(f), rect(box), fullText(text), charsPerSecond(cps), elapsedTime(0), visibleChars(0) {
    wrapText();
}

void TextBox::setText(const std::string& newText) {
    fullText = newText;
    elapsedTime = 0;
    visibleChars = 0;
    wrapText();
}

bool TextBox::isDone() const {
    return visibleChars >= (int)fullText.size();
}

void TextBox::update(Uint32 deltaTime) {
    elapsedTime += deltaTime;
    visibleChars = (elapsedTime / 1000.0f) * charsPerSecond;
    if (visibleChars > (int)fullText.size())
        visibleChars = fullText.size();
}

void TextBox::render() {
    int lineHeight = TTF_FontHeight(font);
    int y = rect.y;
    int charsLeft = visibleChars;

    for (const std::string& line : wrappedLines) {
        if (charsLeft <= 0) break;

        std::string visibleLine = line.substr(0, std::min((int)line.size(), charsLeft));

        SDL_Surface* surface = TTF_RenderText_Blended(font, visibleLine.c_str(), {255, 255, 255, 255});
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect dst = {rect.x, y, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, nullptr, &dst);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        y += lineHeight;
        charsLeft -= line.size();
    }
}

void TextBox::wrapText() {
    wrappedLines.clear();

    std::istringstream stream(fullText);
    std::string word, line;

    while (stream >> word) {
        std::string testLine = line.empty() ? word : line + " " + word;
        int w = 0, h = 0;
        TTF_SizeText(font, testLine.c_str(), &w, &h);
        if (w > rect.w) {
            if (!line.empty()) wrappedLines.push_back(line);
            line = word;
        } else {
            line = testLine;
        }
    }
    if (!line.empty()) wrappedLines.push_back(line);
}
