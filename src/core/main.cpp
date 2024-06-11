/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** main.cpp
*/
#include <dlfcn.h>
#include <iostream>
#include <chrono>
#include "../../include/Core.hpp"
#include <regex>
#include <filesystem>

Arcade::Core::Core(std::string graphique_lib)
{
    std::ifstream file(graphique_lib);
    if (!file.good()) {
        throw Exception("File does not exist: " + graphique_lib);
    }
    graphique_handle = dlopen(graphique_lib.c_str(), RTLD_LAZY);
    game_handle = dlopen("./lib/arcade_user.so", RTLD_LAZY);
    if (!graphique_handle) {
        throw Exception(dlerror());
    }
    dlerror();
}

void Arcade::Core::Prepare_function() {
    create_graphique = reinterpret_cast<decltype(create_graphique)>(dlsym(graphique_handle, "create_graphique"));
    create_game = reinterpret_cast<decltype(create_game)>(dlsym(game_handle, "create_game"));
    getType = reinterpret_cast<decltype(getType)>(dlsym(game_handle, "getType"));
}

void Arcade::Core::loadGameLibrary(const std::string& libraryPath) {
    if (game_handle) {
        dlclose(game_handle);
        game_handle = nullptr;
    }
    game_handle = dlopen(libraryPath.c_str(), RTLD_LAZY);
    if (!game_handle) {
        throw Exception(std::string("Failed to load library: ") + dlerror());
    }
    dlerror();
    create_game = reinterpret_cast<decltype(create_game)>(dlsym(game_handle, "create_game"));
    if (!create_game) {
        throw Exception(std::string("Failed to load symbol: ") + dlerror());
    }

    getType = reinterpret_cast<decltype(getType)>(dlsym(game_handle, "getType"));
    if (!getType) {
        throw Exception(std::string("Failed to load symbol for getType: ") + dlerror());
    }
}

std::vector<std::string> Arcade::Core::goto_menu(std::unique_ptr<IGame>& game, std::vector<std::string> map) {
    game.reset();
    loadGameLibrary("./lib/arcade_menu.so");
    game = create_game();
    map = game->init();
    return map;
}

std::vector<std::string> Arcade::Core::change_game_handler(std::unique_ptr<IGame>& game, std::vector<std::string> map) {
    game.reset();
    loadGameLibrary(games_path_list[currentGameIndex]);
    map.clear();
    game = create_game();
    map = game->init();
    graphique->assign_texture(game->get_texture());
    currentGameIndex = (currentGameIndex + 1) % games_path_list.size();
    return map;
}

void Arcade::Core::loadGraphicLibrary(const std::string& libraryPath) {
    if (graphique_handle) {
        dlclose(graphique_handle);
        graphique_handle = nullptr;
    }
    graphique_handle = dlopen(libraryPath.c_str(), RTLD_LAZY);
    if (!graphique_handle) {
        throw Exception(std::string("Failed to load library: ") + dlerror());
    }
    dlerror();
    create_graphique = reinterpret_cast<decltype(create_graphique)>(dlsym(graphique_handle, "create_graphique"));
    if (!create_graphique) {
        throw Exception(std::string("Failed to load symbol: ") + dlerror());
    }
}

std::unique_ptr<IGraphic> Arcade::Core::change_graphique_handler(std::unique_ptr <IGraphic> &graphique)
{
    graphique->destroy_lib();
    graphique.reset();
    loadGraphicLibrary(libs_path_list[currentLibIndex]);
    graphique = create_graphique();
    graphique->init();
    currentLibIndex = (currentLibIndex + 1) % libs_path_list.size();
    return std::move(graphique);
}


std::vector<std::string> Arcade::Core::getSharedLibraries(const std::string &directory) {
    std::vector<std::string> sharedLibraries;
    for (const auto &entry : std::filesystem::directory_iterator(directory)) {
        if (entry.path().extension() == ".so") {
            sharedLibraries.push_back(entry.path());
        }
    }
    return sharedLibraries;
}

void Arcade::Core::fillVectorsFromMap() {
    games_path_list.clear();
    libs_path_list.clear();
    auto sharedLibraries = getSharedLibraries("./lib");
    for (const auto& line : sharedLibraries) {
        void* handle = dlopen(line.c_str(), RTLD_LAZY);
        if (!handle) {
            continue;
        }
        dlerror();
        auto getType = (std::pair<std::string, std::string>(*)())dlsym(handle, "getType");
        if (!getType) {
            dlclose(handle);
            continue;
        }
        auto type = getType();
        dlclose(handle);
        if (type.first == "IGame" && type.second != "user") {
            games_path_list.push_back(line);
        } else if (type.first == "IGraphic") {
            libs_path_list.push_back(line);
        }
    }
}

void Arcade::Core::handleMenu(int& key, std::vector<std::string>& map) {
    if (key == 'E') {
        auto type = getType();
        if (type.first == "IGame" && type.second == "user") {
            std::string userLine = map[5];
            size_t start = userLine.find('@');
            size_t end = userLine.rfind('@');
            if (start < end) {
                this->user_name = userLine.substr(start + 1, end - start - 1);
                map = this->goto_menu(game, map);
            }
        }
        else if (type.first == "IGame" && type.second == "menu") {
            std::regex regex(">([@$])([^@$]+)[@$]");
            for (const auto& line : map) {
                std::sregex_iterator next(line.begin(), line.end(), regex);
                std::sregex_iterator end;
                bool hasSwitched1 = false;
                bool hasSwitched2 = false;
                std::vector<std::string> tempMap = map;
                while (next != end) {
                    std::smatch match = *next;
                    std::string libType = match.str(1);
                    std::string libName = match.str(2);
                    if (libType == "$") {
                        graphique->destroy_lib();
                        graphique.reset();
                        loadGraphicLibrary("./lib/" + libName);
                        graphique = create_graphique();
                        graphique->init();
                        hasSwitched1 = true;
                        graphique->assign_texture(game->get_texture());
                    }
                    else if (libType == "@") {
                        game.reset();
                        loadGameLibrary("./lib/" + libName);
                        tempMap.clear();
                        game = create_game();
                        tempMap = game->init();
                        hasSwitched2 = true;
                        graphique->assign_texture(game->get_texture());
                    }
                    next++;
                }
                if (hasSwitched1 || hasSwitched2) {
                    map = tempMap;
                }
            }
        }
    }
}

void Arcade::Core::run()
{
    int key = 0;
    int score = 0;
    int high_score = 0;
    graphique = create_graphique();
    game = create_game();
    std::vector<std::string> map = game->init();
    graphique->init();
    graphique->assign_texture(game->get_texture());
    fillVectorsFromMap();
    while (true) {
        if (key == 32) {
            graphique->destroy_lib();
            break;
        }
        else if (key == 27)
            map = goto_menu(game, map);
        else if (key == 103)
            map = change_game_handler(game, map);
        else if (key == 108) {
            graphique = change_graphique_handler(graphique);
            graphique->assign_texture(game->get_texture());
        } else if (key == 'r') {
            game.reset();
            map.clear();
            game = create_game();
            map = game->init();
        }
        handleMenu(key, map);
        key = graphique->get_key();
        game->receive_info(key, user_name);
        map = game->get_map_n_edit(map);
        score = game->get_score();
        high_score = game->get_highscore();
        graphique->display(map, score, high_score, user_name);
        graphique->my_refresh();
    }
}

int main(int ac, char **av) {
    (void) ac;
    if (strcmp(av[1], "-h") == 0 || strcmp(av[1], "--help") == 0) {
        std::cout << "USAGE\n\t./arcade path_to_graphique_lib" << std::endl;
        return 0;
    }
    try {
        Arcade::Core test(av[1]);
        test.Prepare_function();
        test.run();
    } catch (const std::exception& e) {
        std::cerr << "Error : " << e.what() << '\n';
        return 84;
    }
    return 0;
}
