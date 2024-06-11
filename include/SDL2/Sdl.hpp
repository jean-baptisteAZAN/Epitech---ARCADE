/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Sdl.hpp
*/
#include "../IGraphic.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>

class Sdl : public IGraphic {
    public:
    Sdl() = default;
    ~Sdl() = default;
    void my_refresh() override;
    void init() override;
    int get_key() override;
    bool display(std::vector<std::string> map, int score, int highscore, std::string user) override;
    void destroy_lib() override;

    void assign_texture(std::vector<std::pair<char, std::vector<std::string>>> tab_texture) override;

private:
    std::map<std::string, std::string> list_texture;
    std::vector<std::string> map;
    std::shared_ptr<SDL_Window> window;
    std::shared_ptr<SDL_Renderer> renderer;
    std::shared_ptr<TTF_Font> font;
    SDL_Color textColor;
    SDL_Surface *textSurface;
    SDL_Event event;
    std::shared_ptr<SDL_Texture> textTexture;
    std::vector<std::vector<SDL_Texture*>> textTextures;
    int textHeight;
    std::unordered_map<std::string, SDL_Texture*> textureCache;
    SDL_Texture* createTextureFromColor(SDL_Color color);
    void updateTextures(std::vector<std::string> map);
    std::vector<std::pair<char, std::vector<std::string>>> _tab_texture;

    SDL_Texture* setTexture(char c);

    void renderTextTexture(SDL_Texture* texture, SDL_Point position);
    SDL_Texture* createTextTexture(const std::string& text);
};
