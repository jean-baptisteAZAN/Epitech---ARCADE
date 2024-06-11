/*
** EPITECH PROJECT, 2024
** B-OOP-400-LIL-4-1-arcade-theo.lemaire
** File description:
** ncurse
*/

#include "../../../include/NCURSES/ncurse.hpp"

void Ncurse::my_refresh() {
    refresh();
}

void Ncurse::assign_texture(std::vector<std::pair<char, std::vector<std::string>>> tab_texture)
{
    clear();
    _tab_texture = tab_texture;
}

void Ncurse::init() {
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    nodelay(stdscr, TRUE);
    clear();

    int colorId = 1;
    for (const auto& texture : _tab_texture) {
        int r, g, b;
        r = std::stoi(texture.second[0]);
        g = std::stoi(texture.second[1]);
        b = std::stoi(texture.second[2]);
        init_color(colorId, r * 1000 / 255, g * 1000 / 255, b * 1000 / 255);
        init_pair(colorId, colorId, COLOR_BLACK);
        charTexturePairs[texture.first] = colorId;
        colorId++;
    }
}

bool Ncurse::display(std::vector<std::string> map, int score, int highscore, std::string user) {
    for (size_t i = 0; i < map.size(); ++i) {
        move(i, 0);
        for (const char& c : map[i]) {
            if (charTexturePairs.count(c) > 0) {
                attron(COLOR_PAIR(charTexturePairs[c]));
                addch(c);
                attroff(COLOR_PAIR(charTexturePairs[c]));
            } else {
                addch(c);
            }
        }
    }
    mvprintw(map.size() + 1, 0, ("Score: " + std::to_string(score)).c_str());
    mvprintw(map.size() + 2, 0, ("Highscore: " + std::to_string(highscore)).c_str());
    mvprintw(map.size() + 3, 0, ("Username: " + user).c_str());
    return true;
}

int Ncurse::get_key() {
    int ch = getch();
    if (ch == KEY_UP)
        return 'U';
    if (ch == KEY_DOWN)
        return 'D';
    if (ch == KEY_LEFT)
        return 'L';
    if (ch == KEY_RIGHT)
        return 'R';
    if (ch == 10)
        return 'E';
    if (ch == 114)
        return 'r';
    return ch;
}

void Ncurse::destroy_lib() {
    clear();
    endwin();
}

extern "C" {
    std::unique_ptr<IGraphic> create_graphique() {
        return  std::make_unique<Ncurse>();
    }
    std::pair<std::string, std::string> getType() {
        return std::make_pair("IGraphic", "ncurse");
    }
}
