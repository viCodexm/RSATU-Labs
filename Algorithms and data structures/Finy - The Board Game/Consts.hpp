#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


const int SCREEN_WIDTH = 305;
const int SCREEN_HEIGHT = 650;
const int CELL_WIDTH = 60, CELL_OUTLINE = 4, CELL_OFFSET = CELL_WIDTH + CELL_OUTLINE * 3;
const sf::Color COLOR_BACKGROUND(120, 120, 120), COLOR_LIGHT(50, 50, 50),
            COLOR_BASIC(150, 150, 150), COLOR_BASIC_PRESS = COLOR_BASIC + COLOR_LIGHT,
            COLOR_BLUE(150, 150, 220), COLOR_BLUE_PRESS = COLOR_BLUE + COLOR_LIGHT,
            COLOR_RED(200, 150, 150), COLOR_RED_PRESS = COLOR_RED + COLOR_LIGHT,
            COLOR_BACKGROUND_BLUE = COLOR_BLUE - COLOR_LIGHT - COLOR_LIGHT,
            COLOR_BACKGROUND_RED = COLOR_RED - COLOR_LIGHT - COLOR_LIGHT,
            COLOR_GREEN(118, 176, 122);