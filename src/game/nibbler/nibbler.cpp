/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** nibbler
*/

#include "../../../include/game/nibbler.hpp"
#include <algorithm>

std::vector<std::string> Nibbler::init() {
    std::vector<std::string> map  = {
            "####################",
            "#&&&&&&&&&&&&&&&&&&#",
            "####################",
            "####################",
            "#  A   A   A   A   #",
            "# ### # ### # ###  #",
            "#A# #A#     #A# #A #",
            "# ### # # # # ###  #",
            "#     #A# #A#      #",
            "# ##### # # #####  #",
            "#A# A         A #A #",
            "# # #####A##### #  #",
            "#   A         A    #",
            "# ##### ### #####  #",
            "#  A    # #    A   #",
            "# ### # ### # ###  #",
            "# # # #     # # #  #",
            "# ### # ### # ###  #",
            "#A    # # # #    A #",
            "# ##### ### #####  #",
            "#     0XXX         #",
            "####################"
    };
    std::string line;
    dir = LEFT;
    len = 4;
    point = 0;
    find_head(map);
    std::string& timerLine = map[1];
    size_bar = std::count(timerLine.begin(), timerLine.end(), '&') / 8;
    return map;
}

void Nibbler::receive_info(int _key, std::string username) {
    key = _key;
    this->username = username;
}

std::vector<std::pair<char, std::vector<std::string>>> Nibbler::get_texture()
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

void Nibbler::find_head(std::vector<std::string>& map) {
    char head = '0';
    char body = 'X';
    for (size_t y = 0; y < map.size(); ++y) {
        for (size_t x = 0; x < map[y].size(); ++x) {
            if (map[y][x] == head) {
                nibbler.push_back(SnakeSegment{x, y});
            }
        }
    }
    for (size_t y = 0; y < map.size(); ++y) {
        for (size_t x = 0; x < map[y].size(); ++x) {
            if (map[y][x] == body) {
                nibbler.push_back(SnakeSegment{x, y});
            }
        }
    }
}

void Nibbler::moove(std::vector<std::string>& map) {
    std::vector<SnakeSegment> tempo = nibbler;
    std::vector<std::string> tempo_map = map;
    if (dir == TOP) {
        if (map[nibbler[0].y - 1][nibbler[0].x] == '#')
            return;
         if (map[nibbler[0].y - 1][nibbler[0].x] == 'X')
            return loose(map);
        map[nibbler[0].y - 1][nibbler[0].x] = map[nibbler[0].y][nibbler[0].x];
        map[nibbler[0].y][nibbler[0].x] = ' ';
        nibbler[0].y -= 1;
        for(int i = 1; i < len; i++) {
            map[tempo[i - 1].y][tempo[i - 1].x] = map[nibbler[i].y][nibbler[i].x];
            map[nibbler[i].y][nibbler[i].x] =  ' ';
            nibbler[i].y = tempo[i - 1].y;
            nibbler[i].x = tempo[i - 1].x;
        }
        if (map[nibbler[0].y - 1][nibbler[0].x] == 'A'){
            map[tempo[len - 1].y][tempo[len - 1].x] = 'X';
            nibbler.push_back(SnakeSegment{tempo[len - 1].x, tempo[len - 1].y});
            len++;
            point++;
            reset_counter(map);
        }
    }
    if (dir == RIGHT) {
        if (map[nibbler[0].y][nibbler[0].x + 1] == '#')
            return;
         if (map[nibbler[0].y][nibbler[0].x + 1] == 'X')
            return loose(map);
        map[nibbler[0].y][nibbler[0].x + 1] = map[nibbler[0].y][nibbler[0].x];
        map[nibbler[0].y][nibbler[0].x] = ' ';
        nibbler[0].x += 1;
        for(int i = 1; i < len; i++) {
            map[tempo[i - 1].y][tempo[i - 1].x] = map[nibbler[i].y][nibbler[i].x];
            map[nibbler[i].y][nibbler[i].x] =  ' ';
            nibbler[i].y = tempo[i - 1].y;
            nibbler[i].x = tempo[i - 1].x;
        }
        if (map[nibbler[0].y][nibbler[0].x + 1] == 'A'){
            map[tempo[len - 1].y][tempo[len - 1].x] = 'X';
            nibbler.push_back(SnakeSegment{tempo[len - 1].x, tempo[len - 1].y});
            len++;
            point++;
            reset_counter(map);
        }
    }
    if (dir == BOT) {
        if (map[nibbler[0].y + 1][nibbler[0].x] == '#')
            return;
         if (map[nibbler[0].y + 1][nibbler[0].x] == 'X')
            return loose(map);
        map[nibbler[0].y + 1][nibbler[0].x] = map[nibbler[0].y][nibbler[0].x];
        map[nibbler[0].y][nibbler[0].x] = ' ';
        nibbler[0].y += 1;
        for(int i = 1; i < len; i++) {
            map[tempo[i - 1].y][tempo[i - 1].x] = map[nibbler[i].y][nibbler[i].x];
            map[nibbler[i].y][nibbler[i].x] =  ' ';
            nibbler[i].y = tempo[i - 1].y;
            nibbler[i].x = tempo[i - 1].x;
        }
        if (map[nibbler[0].y + 1][nibbler[0].x] == 'A'){
            map[tempo[len - 1].y][tempo[len - 1].x] = 'X';
            nibbler.push_back(SnakeSegment{tempo[len - 1].x, tempo[len - 1].y});
            len++;
            point++;
            reset_counter(map);
        }
    }
    if (dir == LEFT) {
        if (map[nibbler[0].y][nibbler[0].x - 1] == '#')
            return;
         if (map[nibbler[0].y][nibbler[0].x - 1] == 'X')
            return loose(map);
        map[nibbler[0].y][nibbler[0].x  - 1] = map[nibbler[0].y][nibbler[0].x];
        map[nibbler[0].y][nibbler[0].x] = ' ';
        nibbler[0].x -= 1;
        for(int i = 1; i < len; i++) {
            map[tempo[i - 1].y][tempo[i - 1].x] = map[nibbler[i].y][nibbler[i].x];
            map[nibbler[i].y][nibbler[i].x] =  ' ';
            nibbler[i].y = tempo[i - 1].y;
            nibbler[i].x = tempo[i - 1].x;
        }
        if (map[nibbler[0].y][nibbler[0].x - 1] == 'A'){
            map[tempo[len - 1].y][tempo[len - 1].x] = 'X';
            nibbler.push_back(SnakeSegment{tempo[len - 1].x, tempo[len - 1].y});
            len++;
            point++;
            reset_counter(map);
        }
    }
}

std::vector<std::string> Nibbler::get_new_map(std::string path) {
    std::vector<std::string> map;
    std::ifstream file(path);
    std::string line;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            map.push_back(line);
        }
        file.close();
    } else {
        std::cerr << "Failed to open file" << std::endl;
    }
    map.push_back("@score : O@");
    find_head(map);
    return map;
}

void Nibbler::new_lvl(std::vector<std::string>& map) {
    std::vector<SnakeSegment> new_nibbler;
    if (level == 1) {
        map = get_new_map("./configFiles/nibbler_lvl2.txt");
        char head = '0';
        char body = 'X';
        for (size_t y = 0; y < map.size(); ++y) {
            for (size_t x = 0; x < map[y].size(); ++x) {
                if (map[y][x] == head) {
                    new_nibbler.push_back(SnakeSegment{x, y});
                }
            }
        }
        for (size_t y = 0; y < map.size(); ++y) {
            for (size_t x = 0; x < map[y].size(); ++x) {
                if (map[y][x] == body) {
                    new_nibbler.push_back(SnakeSegment{x, y});
                }
            }
        }
        nibbler = new_nibbler;
        len = 4;
        dir = LEFT;
    }
}

void Nibbler::verif_apple(std::vector<std::string>& map) {
    bool find = false;
    for (size_t y = 0; y < map.size(); ++y) {
        for (size_t x = 0; x < map[y].size(); ++x) {
            if (map[y][x] == 'A') {
                find = true;
            }
        }
    }

    if (!find){
        level++;
        new_lvl(map);
    }
}

void Nibbler::loose(std::vector<std::string>& map) {
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
    map.push_back("@score : " + std::to_string(point) + "@");
    finish = true;
}

void Nibbler::reset_counter(std::vector<std::string>& map) {
    for (int i = 0; map[1][i]; i++) {
        if (map[1][i] == '%') {
            map[1][i] = '&';
        }
    }
    timer = 0;
}

std::vector<std::string> Nibbler::get_map_n_edit(std::vector<std::string> map) {
    if (finish)
        return map;

    auto currentTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = currentTime - lastUpdateTime;
    std::chrono::duration<double> elapsedSeconds_two = currentTime - lastUpdateTime_two;
    verif_apple(map);

    if (elapsedSeconds_two.count() >= 1) {
        timer++;
        lastUpdateTime_two = currentTime;
        for (int i = 0, transformed = 0; map[1][i]; i++) {
            if (map[1][i] == '&' && transformed < size_bar) {
                map[1][i] = '%';
                transformed++;
            }
        }

        if (timer >= 10){
            loose(map);
            return map;
        }
    }

    if ((key == 'U' && map[nibbler[0].y -1][nibbler[0].x] == '#') || (key == 'D' && map[nibbler[0].y +1][nibbler[0].x] == '#') ||(key == 'L' && map[nibbler[0].y][nibbler[0].x -1] == '#') ||(key == 'R' && map[nibbler[0].y][nibbler[0].x + 1] == '#') );
    else if (!(key == 'U' && dir == BOT) && !(key == 'D' && dir == TOP) && !(key == 'L' && dir == RIGHT) && !(key == 'R' && dir == LEFT)) {
        switch (key) {
            case 'U':
                dir = TOP;
                // moveUp(map);
                break;
            case 'D':
                dir = BOT;
                // moveDown(map);
                break;
            case 'L':
                dir = LEFT;
                // moveLeft(map);
                break;
            case 'R':
                dir = RIGHT;
                // moveRight(map);
                break;
        }
    }
    if (elapsedSeconds.count() >= 0.1) {
        moove(map);
        lastUpdateTime = currentTime;
    }

    return map;
}

int Nibbler::get_score() {
    return point;
}

void Nibbler::verif_file() {
    std::string file_path = "./configFiles/Nibbler/" + username + ".txt";
    std::ifstream fichierTest(file_path);
    if (!fichierTest.is_open()) {
        std::ofstream fichierOut(file_path);
        if (fichierOut.is_open()) {
            fichierOut << 0; // Écrit 0 dans le fichier si celui-ci n'existait pas
            fichierOut.close();
        }
    } else {
        fichierTest.close();
    }
}

int Nibbler::get_highscore() {
    std::string file_path = "./configFiles/Nibbler/" + username + ".txt";
    verif_file();
    std::ifstream fichier(file_path);
    int nombre = 0;

    if (fichier.is_open()) {
        fichier >> nombre;
        fichier.close(); // Fermez le fichier après la lecture pour pouvoir le réouvrir en écriture

        if (point > nombre) {
            // Réouvrir le fichier en mode écriture, ce qui va effacer le contenu précédent
            std::ofstream fichierOut(file_path, std::ios::trunc);
            if (fichierOut.is_open()) {
                fichierOut << point; // Écrivez le nouveau score
                fichierOut.close(); // Fermez le fichier après l'écriture
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
        return  std::make_unique<Nibbler>();
    }
    std::pair<std::string, std::string> getType() {
        return std::make_pair("IGame", "nibbler");
    }
}
