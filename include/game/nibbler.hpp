//
// Created by theo on 3/14/24.
//

#ifndef B_OOP_400_LIL_4_1_ARCADE_THEO_LEMAIRE_NIBBLER_HPP
#define B_OOP_400_LIL_4_1_ARCADE_THEO_LEMAIRE_NIBBLER_HPP

#include "../IGame.hpp"
#include <chrono>
#include <iostream>
#include <fstream>
#include <memory>

class Nibbler : public IGame {
    enum Direction {
        TOP,
        BOT,
        RIGHT,
        LEFT
    };

public:
    Nibbler() = default;
    virtual ~Nibbler() = default;
    std::vector<std::string> init() override;
    std::vector<std::string> get_map_n_edit(std::vector<std::string> map) override;
    void receive_info(int key, std::string username) override;
    int get_score() override;
    int get_highscore() override;
    std::vector<std::pair<char, std::vector<std::string>>> get_texture() override;

private:
    struct SnakeSegment {
        size_t x;
        size_t y;
    };
    int len;
    int point = 0;
    std::chrono::time_point<std::chrono::system_clock> lastUpdateTime = std::chrono::system_clock::now();
    std::chrono::time_point<std::chrono::system_clock> lastUpdateTime_two = std::chrono::system_clock::now();
    int size_bar = 0;
    Direction dir;
    int key;
    int timer = 0;
    int level = 0;
    void find_head(std::vector<std::string>& map);
    std::vector<SnakeSegment> nibbler;
    bool finish = false;
    std::string username;

    void moove(std::vector<std::string>& map);
    void verif_apple(std::vector<std::string>& map);
    void loose(std::vector<std::string>& map);
    void new_lvl(std::vector<std::string>& map);
    std::vector<std::string> get_new_map(std::string);
    void reset_counter(std::vector<std::string>& map);
    void verif_file();
};

#endif //B_OOP_400_LIL_4_1_ARCADE_THEO_LEMAIRE_NIBBLER_HPP
