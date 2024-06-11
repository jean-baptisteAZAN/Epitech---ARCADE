//
// Created by theo on 3/13/24.
//

#ifndef B_OOP_400_LIL_4_1_ARCADE_THEO_LEMAIRE_CORE_HPP
#define B_OOP_400_LIL_4_1_ARCADE_THEO_LEMAIRE_CORE_HPP

#include <vector>
#include "IGraphic.hpp"
#include "IGame.hpp"
#include "game/Menu.hpp"
#include <exception>
#include <cstring>

namespace Arcade {

    class Core {
    public:
        Core(std::string graphique_lib);
        ~Core() = default;
        void run();
        void Prepare_function();
        void loadGameLibrary(const std::string& libraryPath);
        std::vector<std::string> change_game_handler(std::unique_ptr<IGame>& game, std::vector<std::string> map);
        std::unique_ptr<IGraphic> change_graphique_handler(std::unique_ptr<IGraphic>& graphique);
        std::vector<std::string> goto_menu(std::unique_ptr<IGame>& game, std::vector<std::string> map);
        void handleMenu(int& key, std::vector<std::string>& map);
        void loadGraphicLibrary(const std::string& libraryPath);

        std::vector<std::string> getSharedLibraries(const std::string &directory);
        class Exception : public std::exception {
        public:
            Exception(std::string message) : _message(std::move(message)) {}
            const char *what() const noexcept override {
                    return _message.c_str();
            }
        private:
            std::string _message;
        };

    private:
        std::vector<std::string> map;
        std::add_pointer_t<void> graphique_handle;
        std::add_pointer_t<void> game_handle;
        std::unique_ptr<IGraphic> graphique;
        std::unique_ptr<IGame> game;
//------------Graphique function------------------//
        std::add_pointer_t<std::unique_ptr<IGraphic>()>create_graphique;
//----------------Game function------------------//
        std::add_pointer_t<std::unique_ptr<IGame>()>create_game;
//----------------getType function------------------//
        std::add_pointer_t<std::pair<std::string, std::string>()>getType;


        std::vector<std::string> games_path_list;
        std::vector<std::string> libs_path_list;
        void fillVectorsFromMap();
        size_t currentGameIndex = 0;
        size_t currentLibIndex = 0;

        std::string user_name;
    };
}

#endif //B_OOP_400_LIL_4_1_ARCADE_THEO_LEMAIRE_CORE_HPP
