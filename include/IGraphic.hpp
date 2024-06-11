//
// Created by theo on 3/13/24.
//

#ifndef B_OOP_400_LIL_4_1_ARCADE_THEO_LEMAIRE_GRAPHIQUE_LIB_HPP
#define B_OOP_400_LIL_4_1_ARCADE_THEO_LEMAIRE_GRAPHIQUE_LIB_HPP

#include <vector>
#include <iostream>
#include <map>
#include "memory"
#include "exception"

class IGraphic {
public:
    IGraphic() = default;
    virtual ~IGraphic() = default;
    virtual void my_refresh() = 0;
    virtual void init() = 0;
    virtual int get_key() = 0;
    virtual bool display(std::vector<std::string> map, int score, int highscore, std::string user) = 0;
    virtual void destroy_lib() = 0;

    virtual void assign_texture(std::vector<std::pair<char, std::vector<std::string>>> tab_texture) = 0;

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
    std::map<std::string, std::string> list_texture;
    std::vector<std::string> map;
};


#endif //B_OOP_400_LIL_4_1_ARCADE_THEO_LEMAIRE_GRAPHIQUE_LIB_HPP
