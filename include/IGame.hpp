//
// Created by theo on 3/14/24.
//

#ifndef B_OOP_400_LIL_4_1_ARCADE_THEO_LEMAIRE_IGAME_HPP
#define B_OOP_400_LIL_4_1_ARCADE_THEO_LEMAIRE_IGAME_HPP

#include "vector"
#include "string"


class IGame {
public :
    IGame() = default;
    virtual ~IGame() = default;
    virtual std::vector<std::string> init() = 0;
    virtual std::vector<std::string> get_map_n_edit(std::vector<std::string> map) = 0;
    virtual void receive_info(int key, std::string username) = 0;
    virtual int get_score() = 0;
    virtual int get_highscore() = 0;

    virtual std::vector<std::pair<char, std::vector<std::string>>> get_texture() = 0;
};

#endif //B_OOP_400_LIL_4_1_ARCADE_THEO_LEMAIRE_IGAME_HPP
