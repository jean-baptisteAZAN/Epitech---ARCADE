/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** sdl2.cpp
*/
#include "../../../include/SDL2/Sdl.hpp"

void Sdl::my_refresh() {
    SDL_RenderPresent(renderer.get());
}

void Sdl::assign_texture(std::vector<std::pair<char, std::vector<std::string>>> tab_texture)
{
    _tab_texture = tab_texture;
}

SDL_Texture* Sdl::createTextureFromColor(SDL_Color color)
{
    SDL_Surface* surface = SDL_CreateRGBSurface(0, 30, 30, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, color.r, color.g, color.b));
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer.get(), surface);
    SDL_FreeSurface(surface);
    return texture;
}

SDL_Texture* Sdl::setTexture(char c)
{
    std::string key(1, c);

    if (textureCache.count(key) == 0) {
        for (size_t i = 0; i < _tab_texture.size(); ++i) {
            if (_tab_texture[i].first == c) {
                SDL_Color color;
                color.r = std::stoi(_tab_texture[i].second[0]);
                color.g = std::stoi(_tab_texture[i].second[1]);
                color.b = std::stoi(_tab_texture[i].second[2]);
                textureCache[key] = createTextureFromColor(color);
            }
        }
    }
    return textureCache[key];
}

void Sdl::updateTextures(std::vector<std::string> map) {
    textTextures.clear();
    for (const auto &line : map) {
        std::vector<SDL_Texture*> lineTextures;
        for (size_t i = 0; i < line.size(); ++i) {
            SDL_Texture* texture = nullptr;
            char c = line[i];
            if (line[i] == '@' || line[i] == '$') {
                size_t end = line.find(c, i + 1);
                if (end != std::string::npos) {
                    std::string text = line.substr(i + 1, end - i - 1);
                    if (textureCache.count(text) == 0) {
                        SDL_Surface *surface = TTF_RenderText_Solid(font.get(), text.c_str(), textColor);
                        texture = SDL_CreateTextureFromSurface(renderer.get(), surface);
                        textureCache[text] = texture;
                        SDL_FreeSurface(surface);
                    } else {
                        texture = textureCache[text];
                    }
                    lineTextures.push_back(texture);
                    i = end;
                }
            }
            else {
                texture = setTexture(line[i]);
                lineTextures.push_back(texture);
            }
        }
        textTextures.push_back(lineTextures);
    }
}

SDL_Texture* Sdl::createTextTexture(const std::string& text) {
    if (textureCache.count(text) == 0) {
        SDL_Surface *surface = TTF_RenderText_Solid(font.get(), text.c_str(), textColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer.get(), surface);
        textureCache[text] = texture;
        SDL_FreeSurface(surface);
    }
    return textureCache[text];
}

void Sdl::renderTextTexture(SDL_Texture* texture, SDL_Point position) {
    int textWidth, textHeight;
    SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);
    SDL_Rect textRect = {position.x, position.y, textWidth, textHeight};
    SDL_RenderCopy(renderer.get(), texture, NULL, &textRect);
}

bool Sdl::display(std::vector<std::string> map, int score, int highscore, std::string user) {
    (void)score;
    (void)highscore;
    updateTextures(map);
    SDL_RenderClear(renderer.get());
    SDL_RenderCopy(renderer.get(), textTexture.get(), NULL, NULL);
    int blockSize = 30;
    for (size_t i = 0; i < textTextures.size(); i++) {
        for (size_t j = 0; j < textTextures[i].size(); j++) {
            SDL_Texture* textTexture = textTextures[i][j];
            int textWidth, textHeight;
            SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);
            SDL_Rect textRect = {static_cast<int>(j * blockSize), static_cast<int>(i * blockSize), textWidth, textHeight};
            SDL_RenderCopy(renderer.get(), textTexture, NULL, &textRect);
        }
    }
    std::string scoreText = "Score: " + std::to_string(score);
    SDL_Texture* scoreTexture = createTextTexture(scoreText);
    renderTextTexture(scoreTexture, {10, 800});
    std::string highScoreText = "High Score: " + std::to_string(highscore);
    SDL_Texture* highScoreTexture = createTextTexture(highScoreText);
    renderTextTexture(highScoreTexture, {10, 850});
    std::string userText = "Player: " + user;
    SDL_Texture* userTexture = createTextTexture(userText);
    renderTextTexture(userTexture, {10, 900});

    return true;
}

void Sdl::init() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    window = std::shared_ptr<SDL_Window>(SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN), SDL_DestroyWindow);
    renderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer);
    font = std::shared_ptr<TTF_Font>(TTF_OpenFont("./assets/montserrat.regular.ttf", 24), TTF_CloseFont);
    textColor = {0, 0, 255, 255};
}

void Sdl::destroy_lib() {
    for (auto& pair : textureCache) {
        SDL_DestroyTexture(pair.second);
    }
    textureCache.clear();
    SDL_FreeSurface(Sdl::textSurface);
    font.reset();
    renderer.reset();
    window.reset();
    TTF_Quit();
    SDL_Quit();
}

int Sdl::get_key() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return -1;
        }
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_UP)
                return 'U';
            else if (event.key.keysym.sym == SDLK_DOWN)
                return 'D';
            else if (event.key.keysym.sym == SDLK_LEFT)
                return 'L';
            else if (event.key.keysym.sym == SDLK_RIGHT)
                return 'R';
            else if (event.key.keysym.sym == SDLK_RETURN)
                return 'E';
            else if (event.key.keysym.sym == SDLK_r)
                return 'r';
            return event.key.keysym.sym;
        }
    }
    return 0;
}

extern "C" {
    std::unique_ptr<IGraphic> create_graphique() {
        return  std::make_unique<Sdl>();
    }
    std::pair<std::string, std::string> getType() {
        return std::make_pair("IGraphic", "sdl2");
    }
}

