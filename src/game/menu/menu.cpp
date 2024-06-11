/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** menu.cpp
*/

#include "../../../include/game/Menu.hpp"
#include <dlfcn.h>

std::pair<std::vector<std::string>, std::vector<std::string>> Menu::getSharedLibraries(const std::string &directory) {
    struct dirent *entry;
    DIR *dir = opendir(directory.c_str());

    if (dir == nullptr) {
        return {games, libraries};
    }

    while ((entry = readdir(dir)) != nullptr) {
        std::string filename = entry->d_name;
        if (filename.size() > 3 && filename.substr(filename.size() - 3) == ".so") {
            void* handle = dlopen((directory + "/" + filename).c_str(), RTLD_LAZY);
            if (handle) {
                auto getType = (std::pair<std::string, std::string>(*)())dlsym(handle, "getType");
                if (getType) {
                    auto [type, subtype] = getType();
                    if (type == "IGame") {
                        games.push_back(filename);
                    } else {
                        libraries.push_back(filename);
                    }
                }
                dlclose(handle);
            }
        }
    }
    closedir(dir);
    return {games, libraries};
}

std::vector<std::string> Menu::write_so_files_to_config() {
    auto so_files = getSharedLibraries("./lib");
    std::vector <std::string> games = so_files.first;
    std::vector <std::string> libraries = so_files.second;

    std::sort(games.begin(), games.end());
    std::sort(libraries.begin(), libraries.end());

    std::vector <std::string> output;
    output.push_back("#####################################################");

    size_t max_size = std::max(games.size(), libraries.size());
    const size_t max_name_length = 15;
    const size_t padding_length = 20;

    for (size_t i = 0; i < max_size; ++i) {
        std::string line;
        if (i < games.size()) {
            line += "# ";
            if (i == currentGameIndex) {
                line += ">";
            } else {
                line += " ";
            }
            line += "@" + games[i] + "@";
            line += std::string(padding_length - std::min(games[i].size(), max_name_length), ' ');
            line += "#";
        } else {
            line += "# " + std::string(padding_length, ' ') + "#";
        }
        line += " ";
        if (i < libraries.size()) {
            if (i == currentLibraryIndex) {
                line += ">";
            } else {
                line += " ";
            }
            line += "$" + libraries[i] + "$";
            line += std::string(padding_length - std::min(libraries[i].size(), max_name_length), ' ');
            line += "#";
        } else {
            line += " " + std::string(padding_length, ' ') + "#";
        }

        output.push_back(line);
    }
        output.push_back("#####################################################");
    return output;
}

std::vector<std::string> Menu::updateMenuWithCursor(const std::vector<std::string>& map, int currentGameIndex, int currentLibraryIndex) {
    std::vector<std::string> updatedMap = map;
    int gameLine = 0;
    int libraryLine = 0;
    for (auto& line : updatedMap) {
        auto cleanLine = [](std::string& line, char marker) {
            size_t pos;
            while ((pos = line.find(">" + std::string(1, marker))) != std::string::npos) {
                line.erase(pos, 1);
            }
        };
        cleanLine(line, '@');
        cleanLine(line, '$');
    }
    for (size_t i = 0; i < updatedMap.size(); ++i) {
        size_t gamePos = updatedMap[i].find("@");
        if (gamePos != std::string::npos) {
            if (gameLine == currentGameIndex && updatedMap[i].find("@") != std::string::npos) {
                updatedMap[i].insert(gamePos, ">");
            }
            gameLine++;
        }
    }
    for (size_t i = 0; i < updatedMap.size(); ++i) {
        size_t libraryPos = updatedMap[i].find("$");
        if (libraryPos != std::string::npos) {
            if (libraryLine == currentLibraryIndex && updatedMap[i].find("$") != std::string::npos) {
                updatedMap[i].insert(libraryPos, ">");
            }
            libraryLine++;
        }
    }
    return updatedMap;
}

std::vector<std::string> Menu::get_map_n_edit(std::vector<std::string> map) {
    bool hasMoved = false;
    switch (_key) {
        case 'L':
            hasMoved = true;
            if (currentLibraryIndex > 0) {
                currentLibraryIndex--;
            }
            break;
        case 'R':
            hasMoved = true;
            if (currentLibraryIndex < libraries.size() - 1) {
                currentLibraryIndex++;
            }
            break;
        case 'U':
            hasMoved = true;
            if (currentGameIndex > 0) {
                currentGameIndex--;
            }
            break;
        case 'D':
            hasMoved = true;
            if (currentGameIndex < games.size() - 1) {
                currentGameIndex++;
            }
            break;
    }
    if (hasMoved) {
        map = updateMenuWithCursor(map, currentGameIndex, currentLibraryIndex);
    }
    return map;
}

std::vector<std::string> Menu::init() {
    std::vector<std::string> _map = write_so_files_to_config();
    return _map;
}

void Menu::receive_info(int key, std::string username) {
    _key = key;
    _username = username;
}

int Menu::get_score() {
    return 0;
}

int Menu::get_highscore() {
    return 0;
}

std::vector<std::pair<char, std::vector<std::string>>> Menu::get_texture()
{
    std::vector<std::pair<char, std::vector<std::string>>> texture;
    texture.push_back(std::make_pair('0', std::vector<std::string>{"176", "224","230"}));
    texture.push_back(std::make_pair('X', std::vector<std::string>{"60", "255", "50"}));
    texture.push_back(std::make_pair('A', std::vector<std::string>{"255", "255", "0"}));
    texture.push_back(std::make_pair('#', std::vector<std::string>{"255", "51", "51"}));
    texture.push_back(std::make_pair('>', std::vector<std::string>{"155", "155", "155"}));
    texture.push_back(std::make_pair(' ', std::vector<std::string>{"0", "0", "0"}));

    return texture;
}


extern "C" {
    std::unique_ptr<IGame> create_game() {
        return  std::make_unique<Menu>();
    }
    std::pair<std::string, std::string> getType() {
        return std::make_pair("IGame", "menu");
    }
}


