/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** sfml.hpp
*/
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "../IGraphic.hpp"
#include <unordered_map>


class Sfml : public IGraphic {
public:
    Sfml() = default;
    ~Sfml() = default;
    void my_refresh() override;
    void init() override;
    int get_key() override;
    bool display(std::vector <std::string> map, int score, int highscore, std::string user) override;
    void destroy_lib() override;

    void assign_texture(std::vector<std::pair<char, std::vector<std::string>>> tab_texture) override;

private:
    std::shared_ptr<sf::RenderWindow> window;
    sf::Font font;
    sf::Color textColor;

    int blockSize = 30;
    int textOffsetY;


    std::vector<std::vector<sf::Texture>> textTextures;
    sf::Texture createBlockTexture(const sf::Color& color);
    void updateTextures(std::vector<std::string> map);
    std::vector<sf::Text> texts;
    sf::Text createText(const std::string &textStr, unsigned int characterSize, float x, float y);

    std::vector<std::pair<char, std::vector<std::string>>> _tab_texture;

    sf::Texture setTexture(char c);
    std::map<char, sf::Texture> textureCache;

    sf::Text scoreText;
    sf::Text highScoreText;
    sf::Text userText;
};
