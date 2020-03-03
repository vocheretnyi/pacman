#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>

#include "path_finder.h"

class Statistics;

//
const std::vector<std::string> FIELD_MAZE = {
        {"!#######################!"},
        {"!#          #          #!"},
        {"!# ## ##### # ##### ## #!"},
        {"!#                     #!"},
        {"!# ## # ######### # ## #!"},
        {"!#    #     #     #    #!"},
        {"!#### ##### # ##### ####!"},
        {"!!!!# #           # #!!!!"},
        {"##### # # ##### # # #####"},
        {"#       # #   # #       #"},
        {"##### # # ##### # # #####"},
        {"!!!!# #           # #!!!!"},
        {"!#### # ######### # ####!"},
        {"!#          #          #!"},
        {"!# ## ##### # ##### ## #!"},
        {"!#  #               #  #!"},
        {"!## # # ######### # #  #!"},
        {"!#    #     #     #    #!"},
        {"!# ####### ### ####### #!"},
        {"!# #     #     #     # #!"},
        {"!# # ### ## # ## ### # #!"},
        {"!# # #      #      # # #!"},
        {"!# # # #### # #### # # #!"},
        {"!#          #          #!"},
        {"!#######################!"},
};
//const std::vector<std::string> FIELD_MAZE = {
//    {"#################"},
//    {"#               #"},
//    {"#               #"},
//    {"#  ###########  #"},
//    {"#  #         #  #"},
//    {"#  #         #  #"},
//    {"#  #         #  #"},
//    {"#  #         #  #"},
//    {"#  #         #  #"},
//    {"#  #         #  #"},
//    {"#  #         #  #"},
//    {"#  #         #  #"},
//    {"#  #         #  #"},
//    {"#               #"},
//    {"#               #"},
//    {"#               #"},
//    {"#################"},
//};

class GameMap {
public:
    GameMap();

    size_t getWidth() const;

    size_t getHeight() const;

    float getBlockSize() const;

    const std::vector<std::vector<sf::RectangleShape>>& getRectangles() const;

    std::queue<sf::Vector2f> createWayTo(float x, float y, const sf::Vector2f& startPos) const;

    void Test() const;

private:
    const float kBlockSize = 25.0;
    size_t width;
    size_t height;
    std::vector<std::vector<sf::RectangleShape> > rectangles;
    PathFinder pathFinder;

    int Round(float x) const;

    std::queue<sf::Vector2f> ConvertToMapCoordinates(const std::vector<sf::Vector2i>& way) const;
};