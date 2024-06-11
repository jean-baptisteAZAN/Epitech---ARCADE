/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Menu.hpp
*/

#pragma once
#include <memory>
#include <vector>
#include <dirent.h>
#include <iostream>
#include "../IGame.hpp"
#include <fstream>
#include <algorithm>

class Menu : public IGame {
public:
    Menu() = default;
    virtual ~Menu() = default;
    std::vector<std::string> init() override;
    void receive_info(int _key, std::string username) override;
    std::vector<std::string> get_map_n_edit(std::vector<std::string> map) override;
    int get_score() override;
    int get_highscore() override;

    std::vector<std::pair<char, std::vector<std::string>>> get_texture() override;
private:
    std::pair<std::vector<std::string>, std::vector<std::string>> getSharedLibraries(const std::string& directory);
    std::vector<std::string> write_so_files_to_config();
    std::vector<std::string> updateMenuWithCursor(const std::vector<std::string>& map, int currentGameIndex, int currentLibraryIndex);
    int _key;
    std::string _username;
    size_t currentGameIndex = 0;
    std::vector<std::string> games;
    std::vector<std::string> libraries;
    size_t currentLibraryIndex = 0;
};
