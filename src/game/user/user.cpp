/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** user.cpp
*/
#include "../../../include/game/User.hpp"

std::vector<std::string> User::init() {
    std::vector<std::string> map;
    map.push_back("#####################################################");
    map.push_back("#           $Bienvenue dans le jeu Arcade$          #");
    map.push_back("#   $Veuillez entrer votre nom pour commencer :$   #");
    map.push_back("#                                                   #");
    map.push_back("#                                                   #");
    map.push_back("#                                                   #");
    map.push_back("#####################################################");

    return map;
}


void User::receive_info(int key, std::string user)
{
    (void)user;
    _key = key;
}

std::vector<std::string> User::get_map_n_edit(std::vector<std::string> map) {
    static std::string::size_type cursorPosition = 0;
    const int nameStartCol = 18;
    const int nameRow = 5;
    map[nameRow][nameStartCol - 1] = '@';
    for (std::string::size_type i = 0; i < playerName.size() && (nameStartCol + i) < map[nameRow].size() - 1; ++i) {
        map[nameRow][nameStartCol + i] = playerName[i];
    }
    map[nameRow][nameStartCol + playerName.size()] = '@';
    if (cursorPosition < playerName.size()) {
        map[nameRow + 1][nameStartCol + cursorPosition] = '^';
    }
    switch (_key) {
        case 'U':
            if (playerName[cursorPosition] < 'Z') {
                playerName[cursorPosition]++;
            } else {
                playerName[cursorPosition] = 'A';
            }
            break;
        case 'D':
            if (playerName[cursorPosition] > 'A') {
                playerName[cursorPosition]--; // S'assurer que cette modification affecte le bon caractère.
            } else {
                playerName[cursorPosition] = 'Z';
            }
            break;
        case 'R':
            if (cursorPosition < playerName.length() - 1) { // Ne pas dépasser la longueur de playerName.
                cursorPosition++;
            }
            break;
        case 'L':
            if (cursorPosition > 0) { // Ne pas aller en dessous de 0.
                cursorPosition--;
            }
            break;
    }
    return map;
}

int User::get_score() {
    return 0;
}

int User::get_highscore() {
    return 0;
}

std::vector<std::pair<char, std::vector<std::string>>> User::get_texture()
{
    std::vector<std::pair<char, std::vector<std::string>>> texture;
    texture.push_back(std::make_pair('0', std::vector<std::string>{"176", "224","230"}));
    texture.push_back(std::make_pair('X', std::vector<std::string>{"60", "255", "50"}));
    texture.push_back(std::make_pair('A', std::vector<std::string>{"255", "255", "0"}));
    texture.push_back(std::make_pair('#', std::vector<std::string>{"255", "51", "51"}));
    texture.push_back(std::make_pair('>', std::vector<std::string>{"155", "155", "155"}));
    texture.push_back(std::make_pair('^', std::vector<std::string>{"255", "255", "255"}));
    texture.push_back(std::make_pair('_', std::vector<std::string>{"176", "224","230"}));
    return texture;
}


extern "C" {
    std::unique_ptr<IGame> create_game() {
        return  std::make_unique<User>();
    }
    std::pair<std::string, std::string> getType() {
        return std::make_pair("IGame", "user");
    }
}
