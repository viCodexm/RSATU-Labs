#pragma once

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;
const int CELL_WIDTH = 60, CELL_OUTLINE = 4, CELL_OFFSET = CELL_WIDTH + CELL_OUTLINE * 3;
const sf::Color COLOR_BACKGROUND(120, 120, 120), COLOR_LIGHT(30, 30, 30),
            COLOR_BASIC(67, 83, 104), COLOR_BASIC_PRESS = COLOR_BASIC + COLOR_LIGHT,
            COLOR_BLUE(164, 203, 255), COLOR_BLUE_PRESS = COLOR_BLUE + COLOR_LIGHT;

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());