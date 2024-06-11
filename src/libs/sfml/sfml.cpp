/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** sfml.cpp
*/

#include "../../../include/SFML/sfml.hpp"


void Sfml::my_refresh()
{
    window->display();
}

void Sfml::assign_texture(std::vector<std::pair<char, std::vector<std::string>>> tab_texture)
{
    _tab_texture = tab_texture;
}

sf::Texture Sfml::createBlockTexture(const sf::Color& color) {
    sf::Texture texture;
    sf::Image image;
    image.create(30, 30, color);
    texture.loadFromImage(image);
    return texture;
}

sf::Text Sfml::createText(const std::string &textStr, unsigned int characterSize, float x, float y) {
    sf::Text text;
    text.setFont(font);
    text.setString(textStr);
    text.setFillColor(textColor);
    text.setCharacterSize(characterSize);
    text.setPosition(x, y);
    return text;
}


void Sfml::init()
{
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1400, 1200), "Arcade", sf::Style::Close);
    if (!font.loadFromFile("./assets/montserrat.regular.ttf")) {
        std::cerr << "Error loading font\n";
    }
    textColor = sf::Color::White;
}

sf::Texture Sfml::setTexture(char c)
{
    if (textureCache.count(c) == 0) {
        for (size_t i = 0; i < _tab_texture.size(); ++i) {
            if (_tab_texture[i].first == c) {
                sf::Color fillColor(std::stoi(_tab_texture[i].second[0]), std::stoi(_tab_texture[i].second[1]), std::stoi(_tab_texture[i].second[2]));
                textureCache[c] = createBlockTexture(fillColor);
            }
        }
    }
    return textureCache[c];
}

void Sfml::updateTextures(std::vector<std::string> map) {
    textTextures.clear();
    texts.clear();

    for (size_t i = 0; i < map.size(); ++i) {
        const auto &line = map[i];
        std::vector<sf::Texture> lineTextures;
        for (size_t j = 0; j < line.size(); ++j) {
            char cell = line[j];
            if (line[j] == '@' || line[j] == '$') {
                char verif = line[j];
                size_t end = line.find(verif, j + 1);
                if (end != std::string::npos) {
                    std::string textStr = line.substr(j + 1, end - j - 1);
                    float posX = static_cast<float>(j * blockSize + blockSize / 2);
                    float posY = static_cast<float>(i * blockSize + textOffsetY);
                    sf::Text text = createText(textStr, 24, posX, posY);
                    texts.push_back(text);
                    j = end;
                }
            } else {
                sf::Texture texture;
                texture = setTexture(cell);
                lineTextures.push_back(texture);
            }
        }
        textTextures.push_back(lineTextures);
    }
}


bool Sfml::display(std::vector<std::string> map, int score, int highscore, std::string user) {
    (void)score;
    (void)highscore;
    updateTextures(map);
    window->clear();
    for (size_t i = 0; i < textTextures.size(); i++) {
        for (size_t j = 0; j < textTextures[i].size(); j++) {
            sf::Sprite sprite(textTextures[i][j]);
            sprite.setPosition(static_cast<float>(j * blockSize), static_cast<float>(i * blockSize));
            window->draw(sprite);
        }
    }
    for (const auto &text : texts) {
        window->draw(text);
    }
    scoreText = createText("Score: " + std::to_string(score), 24, 10, 500);
    window->draw(scoreText);
    highScoreText = createText("High Score: " + std::to_string(highscore), 24, 10, 550);
    window->draw(highScoreText);
    userText = createText("Player: " + user, 24, 10, 600);
    window->draw(userText);
    return true;
}

void Sfml::destroy_lib() {
    window->close();
}

int Sfml::get_key() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::TextEntered) {
            switch (event.key.code) {
                case sf::Keyboard::Up:
                    return 'U';
                case sf::Keyboard::Down:
                    return 'D';
                case sf::Keyboard::Left:
                    return 'L';
                case sf::Keyboard::Right:
                    return 'R';
                case sf::Keyboard::Escape:
                    return 27;
                case sf::Keyboard::Return:
                    return 'E';
                case sf::Keyboard::R:
                    return 'r';
                default:
                    return event.key.code;
            }
        }
    }
    return 0;
}

extern "C" {
    std::unique_ptr<IGraphic> create_graphique() {
        return  std::make_unique<Sfml>();
    }
    std::pair<std::string, std::string> getType() {
        return std::make_pair("IGraphic", "sfml");
    }
}


