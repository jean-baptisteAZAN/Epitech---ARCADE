/*
** EPITECH PROJECT, 2024
** B-OOP-400-LIL-4-1-arcade-theo.lemaire
** File description:
** my_game.cpp
*/

#include "../../../include/game/Snake.hpp"
#include <algorithm>
#include <cstring>



std::vector<std::string> Snake::init() {
    std::vector<std::string> map = {
            "##############################",
            "#                            #",
            "#                       A    #",
            "#                            #",
            "#                            #",
            "#                            #",
            "#                            #",
            "#              0             #",
            "#              X             #",
            "#              X             #",
            "#              X             #",
            "#                            #",
            "#                            #",
            "##############################"
    };

    dir = TOP;
    len = 4;
    find_head(map);
    return map;
}

void Snake::receive_info(int _key, std::string username) {
    this->username = username;
    key = _key;
}

std::vector<std::pair<char, std::vector<std::string>>> Snake::get_texture()
{
    std::vector<std::pair<char, std::vector<std::string>>> texture;
    texture.push_back(std::make_pair('0', std::vector<std::string>{"176", "224","230"}));
    texture.push_back(std::make_pair('X', std::vector<std::string>{"60", "255", "50"}));
    texture.push_back(std::make_pair('A', std::vector<std::string>{"255", "255", "0"}));
    texture.push_back(std::make_pair('#', std::vector<std::string>{"255", "51", "51"}));
    texture.push_back(std::make_pair('&', std::vector<std::string>{ "0", "0", "0" }));
    texture.push_back(std::make_pair('%', std::vector<std::string>{ "255", "255", "255" }));
    texture.push_back(std::make_pair('O', std::vector<std::string>{"255", "255", "0"}));
    return texture;
}


void Snake::find_head(std::vector<std::string>& map) {
    char head = '0';
    char body = 'X';
    for (size_t y = 0; y < map.size(); ++y) {
        for (size_t x = 0; x < map[y].size(); ++x) {
            if (map[y][x] == head) {
                snake.push_back(SnakeSegment{x, y});
            }
        }
    }
    for (size_t y = 0; y < map.size(); ++y) {
        for (size_t x = 0; x < map[y].size(); ++x) {
            if (map[y][x] == body) {
                snake.push_back(SnakeSegment{x, y});
            }
        }
    }
}

void Snake::place_apple(std::vector<std::string>& map) {
    point++;
    int height = map.size() - 1;
    int width = map[0].size();

    srand(time(nullptr));

    bool placed = false;
    while (!placed) {
        int x = rand() % width;
        int y = rand() % height;

        if (map[y][x] == ' ') {
            map[y][x] = 'A';
            placed = true;
        }
    }
}

void Snake::moove(std::vector<std::string>& map) {
    std::vector<SnakeSegment> tempo = snake;
    if (dir == TOP) {
         if (map[snake[0].y - 1][snake[0].x] == 'X' || map[snake[0].y - 1][snake[0].x] == '#')
            return loose(map);
        map[snake[0].y - 1][snake[0].x] = map[snake[0].y][snake[0].x];
        map[snake[0].y][snake[0].x] = ' ';
        snake[0].y -= 1;
        for(int i = 1; i < len; i++) {
            map[tempo[i - 1].y][tempo[i - 1].x] = map[snake[i].y][snake[i].x];
            map[snake[i].y][snake[i].x] =  ' ';
            snake[i].y = tempo[i - 1].y;
            snake[i].x = tempo[i - 1].x;
        }
        if (map[snake[0].y - 1][snake[0].x] == 'A'){
            map[tempo[len - 1].y][tempo[len - 1].x] = 'X';
            snake.push_back(SnakeSegment{tempo[len - 1].x, tempo[len - 1].y});
            len++;
            place_apple(map);
        }
    }
    if (dir == RIGHT) {
         if (map[snake[0].y][snake[0].x + 1] == 'X' || map[snake[0].y][snake[0].x + 1] == '#')
            return loose(map);
        map[snake[0].y][snake[0].x + 1] = map[snake[0].y][snake[0].x];
        map[snake[0].y][snake[0].x] = ' ';
        snake[0].x += 1;
        for(int i = 1; i < len; i++) {
            map[tempo[i - 1].y][tempo[i - 1].x] = map[snake[i].y][snake[i].x];
            map[snake[i].y][snake[i].x] =  ' ';
            snake[i].y = tempo[i - 1].y;
            snake[i].x = tempo[i - 1].x;
        }
        if (map[snake[0].y][snake[0].x + 1] == 'A'){
            map[tempo[len - 1].y][tempo[len - 1].x] = 'X';
            snake.push_back(SnakeSegment{tempo[len - 1].x, tempo[len - 1].y});
            len++;
            place_apple(map);
        }
    }
    if (dir == BOT) {
         if (map[snake[0].y + 1][snake[0].x] == 'X' || map[snake[0].y + 1][snake[0].x] == '#')
            return loose(map);
        map[snake[0].y + 1][snake[0].x] = map[snake[0].y][snake[0].x];
        map[snake[0].y][snake[0].x] = ' ';
        snake[0].y += 1;
        for(int i = 1; i < len; i++) {
            map[tempo[i - 1].y][tempo[i - 1].x] = map[snake[i].y][snake[i].x];
            map[snake[i].y][snake[i].x] =  ' ';
            snake[i].y = tempo[i - 1].y;
            snake[i].x = tempo[i - 1].x;
        }
        if (map[snake[0].y + 1][snake[0].x] == 'A'){
            map[tempo[len - 1].y][tempo[len - 1].x] = 'X';
            snake.push_back(SnakeSegment{tempo[len - 1].x, tempo[len - 1].y});
            len++;
            place_apple(map);
        }
    }
    if (dir == LEFT) {
         if (map[snake[0].y][snake[0].x - 1] == 'X' || map[snake[0].y][snake[0].x - 1] == '#')
            return loose(map);
        map[snake[0].y][snake[0].x  - 1] = map[snake[0].y][snake[0].x];
        map[snake[0].y][snake[0].x] = ' ';
        snake[0].x -= 1;
        for(int i = 1; i < len; i++) {
            map[tempo[i - 1].y][tempo[i - 1].x] = map[snake[i].y][snake[i].x];
            map[snake[i].y][snake[i].x] =  ' ';
            snake[i].y = tempo[i - 1].y;
            snake[i].x = tempo[i - 1].x;
        }
        if (map[snake[0].y][snake[0].x - 1] == 'A'){
            map[tempo[len - 1].y][tempo[len - 1].x] = 'X';
            snake.push_back(SnakeSegment{tempo[len - 1].x, tempo[len - 1].y});
            len++;
            place_apple(map);
        }
    }
}

void Snake::verif_apple(std::vector<std::string>& map) {
    bool find = false;
    for (size_t y = 0; y < map.size(); ++y) {
        for (size_t x = 0; x < map[y].size(); ++x) {
            if (map[y][x] == 'A') {
                find = true;
            }
        }
    }

    if (!find)
        place_apple(map);
}

void Snake::loose(std::vector<std::string>& map) {
    std::vector<std::string> new_map;
    new_map.push_back("##########################################");
    new_map.push_back("#                                        #");
    new_map.push_back("#      OOOO     OOO    O   O   OOOO      #");
    new_map.push_back("#     O        O   O   O O O   O         #");
    new_map.push_back("#     O   OO   OOOOO   O O O   OOOO      #");
    new_map.push_back("#     O    O   O   O   O   O   O         #");
    new_map.push_back("#      OOOOO   O   O   O   O   OOOO      #");
    new_map.push_back("#                                        #");
    new_map.push_back("#                                        #");
    new_map.push_back("#     OOOO    O      O   OOOO   OOOOO    #");
    new_map.push_back("#    O    O   O      O   O      O   O    #");
    new_map.push_back("#    O    O    O    O    OOOO   OOOOO    #");
    new_map.push_back("#    O    O     O  O     O      O  O     #");
    new_map.push_back("#     OOOO       OO      OOOO   O   O    #");
    new_map.push_back("#                                        #");
    new_map.push_back("##########################################");
    map = new_map;
    finish = true;
}

std::vector<std::string> Snake::get_map_n_edit(std::vector<std::string> map) {
    if (finish)
        return map;
    auto currentTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = currentTime - lastUpdateTime;
    verif_apple(map);
    if (!(key == 'U' && dir == BOT) && !(key == 'D' && dir == TOP) && !(key == 'L' && dir == RIGHT) && !(key == 'R' && dir == LEFT)) {
        switch (key) {
            case 'U':
                dir = TOP;
                break;
            case 'D':
                dir = BOT;
                break;
            case 'L':
                dir = LEFT;
                break;
            case 'R':
                dir = RIGHT;
                break;
        }
    }
    if (elapsedSeconds.count() >= 0.1) {
        moove(map);
        lastUpdateTime = currentTime;
    }
    return map;
}

int Snake::get_score() {
    return point;
}

void Snake::verif_file() {
    std::string file_path = "./configFiles/Snake/" + username + ".txt";
    std::ifstream fichierTest(file_path);
    if (!fichierTest.is_open()) {
        std::ofstream fichierOut(file_path);
        if (fichierOut.is_open()) {
            fichierOut << 0;
            fichierOut.close();
        }
    } else {
        fichierTest.close();
    }
}

int Snake::get_highscore() {
    std::string file_path = "./configFiles/Snake/" + username + ".txt";
    verif_file();
    std::ifstream fichier(file_path);
    int nombre = 0;

    if (fichier.is_open()) {
        fichier >> nombre;
        fichier.close();
        if (point > nombre) {
            std::ofstream fichierOut(file_path, std::ios::trunc);
            if (fichierOut.is_open()) {
                fichierOut << point;
                fichierOut.close();
            } else {
                std::cerr << "Impossible d'ouvrir le fichier pour écriture : " << file_path << std::endl;
            }
        }
    } else {
        std::cerr << "Impossible d'ouvrir le fichier : " << file_path << std::endl;
    }
    return nombre;
}

extern "C" {
    std::unique_ptr<IGame> create_game() {
        return  std::make_unique<Snake>();
    }
    std::pair<std::string, std::string> getType() {
        return std::make_pair("IGame", "snake");
    }
}
