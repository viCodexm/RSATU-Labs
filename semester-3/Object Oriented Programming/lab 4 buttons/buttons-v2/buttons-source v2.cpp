
#include <chrono>
#include <random>
#include <mutex>
#include <SFML/Graphics.hpp>
#include "Consts.hpp"
#include "Button.hpp"
#include "Board.hpp"

Board board(2, 8);

void thread_logic(sf::RenderWindow* window) {
    while (window->isOpen()) {
        window->clear(COLOR_BACKGROUND);
        for (Button& cell : board.cells)
            window->draw(cell);
        window->display();
    }
}

int main() {

    
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), L"Кнопки", sf::Style::Titlebar | sf::Style::Close);
    window.setActive(false);
    sf::Thread thread(&thread_logic, &window);
    thread.launch();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                board.can_redistribute = true;
        }
        board.game_logic(window);   
    }
    
    return 0;
}