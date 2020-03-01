#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>

#include "PathFinder.h"

class Statistics;

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

class GameMap {
public:
    GameMap(size_t width = 25, size_t height = 25); // TODO: change

    size_t getWidth() const;

    size_t getHeight() const;

    const std::vector<std::vector<sf::RectangleShape>>& getRectangles() const;

    std::queue<sf::Vector2f> createWayTo(float x, float y, const sf::Vector2f& startPos) const;

private:
    const float BLOCK_SIZE = 25.0;
    size_t _width;
    size_t _height;
    std::vector<std::vector<sf::RectangleShape> > _rectangles;
    PathFinder pathFinder;

    static int Round(float x, float BLOCK_SIZE);

    std::queue<sf::Vector2f> ConvertToMapCoordinats(const std::vector<sf::Vector2i>& way) const;
};