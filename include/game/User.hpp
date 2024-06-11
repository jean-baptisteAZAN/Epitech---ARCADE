/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** User.hpp
*/

#pragma once
#include <memory>
#include <vector>
#include <dirent.h>
#include <iostream>
#include "../IGame.hpp"
#include <fstream>
#include <algorithm>

class User : public IGame {
public:
    User() = default;
    virtual ~User() = default;
    std::vector<std::string> init() override;
    void receive_info(int _key, std::string username) override;
    std::vector<std::string> get_map_n_edit(std::vector<std::string> map) override;
    int get_score() override;
    int get_highscore() override;
    std::vector<std::pair<char, std::vector<std::string>>> get_texture() override;

    private:
        int _key;
        static inline std::string playerName = "NAME";
};
