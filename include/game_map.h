#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>

#include "path_finder.h"
#include "point.h"

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

    std::queue<sf::Vector2f> createWayTo(const sf::Vector2f& fn, const sf::Vector2f& st) const;

    void Test() const;

private:
    const float kBlockSize = 25.0;
    size_t width;
    size_t height;
    std::vector<std::vector<sf::RectangleShape> > rectangles;
    PathFinder pathFinder;

    Point Round(const sf::Vector2f& p) const;

    std::queue<sf::Vector2f> ConvertToMapCoordinates(const std::vector<Point>& way) const;
};