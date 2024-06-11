//
// Created by theo on 3/14/24.
//

#ifndef B_OOP_400_LIL_4_1_ARCADE_THEO_LEMAIRE_SNAKE_HPP
#define B_OOP_400_LIL_4_1_ARCADE_THEO_LEMAIRE_SNAKE_HPP

#include "../IGame.hpp"
#include <iostream>
#include <fstream>
#include <memory>
#include <chrono>
#include <string>

class Snake : public IGame {
    enum Direction {
        TOP,
        BOT,
        RIGHT,
        LEFT
    };

public:
    Snake() = default;
    virtual ~Snake() = default;
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
    int high_score = 0;
    int len;
    std::string username;
    int point = 0;
    std::chrono::time_point<std::chrono::system_clock> lastUpdateTime = std::chrono::system_clock::now();
    Direction dir;
    int key;
    void find_head(std::vector<std::string>& map);
    std::vector<SnakeSegment> snake;
    bool finish = false;

    void moove(std::vector<std::string>& map);
    void place_apple(std::vector<std::string>& map);
    void verif_apple(std::vector<std::string>& map);
    void loose(std::vector<std::string>& map);
    void verif_file();

};

#endif //B_OOP_400_LIL_4_1_ARCADE_THEO_LEMAIRE_SNAKE_HPP
