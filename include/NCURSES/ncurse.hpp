//
// Created by theo on 3/13/24.
//

#ifndef B_OOP_400_LIL_4_1_ARCADE_THEO_LEMAIRE_NCURSE_HPP
#define B_OOP_400_LIL_4_1_ARCADE_THEO_LEMAIRE_NCURSE_HPP

#include "../IGraphic.hpp"
#include <ncurses.h>
#include <fstream>
#include <vector>
#include <iostream>

class Ncurse : public IGraphic {
public:
    Ncurse() = default;
    ~Ncurse() = default;
    void my_refresh() override;
    void init() override;
    int get_key() override;
    bool display(std::vector<std::string> map, int score, int highscore, std::string user) override;
    void destroy_lib() override;

    void assign_texture(std::vector<std::pair<char, std::vector<std::string>>> tab_texture) override;

private:
    std::map<std::string, std::string> list_texture;
    std::vector<std::string> map;

    std::vector<std::pair<char, std::vector<std::string>>> _tab_texture;

    void updateColors(std::vector<std::string> map);
    std::map<char, int> charTexturePairs;
};

#endif //B_OOP_400_LIL_4_1_ARCADE_THEO_LEMAIRE_NCURSE_HPP
