
// includes in Consts.hpp
#include "Board.hpp"

using namespace std;

sf::Color lerp(sf::Color a, sf::Color b, float t) {
   return sf::Color(
       a.r + t * (b.r - a.r),
       a.g + t * (b.g - a.g),
       a.b + t * (b.b - a.b)
   );
}

void round(sf::RenderWindow& window) {
    Board board;
    float t = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();    
                
            if (board.restart)
                return;
        }
        
        if (board.chooseMoveBoard.player_color == 2)
            board.player_move ? t = max(0.0, t - 0.0025) : t = min(1.0, t + 0.0025);
        else board.player_move ? t = min(1.0, t + 0.0025) : t = max(0.0, t - 0.0025);
        
        window.clear(lerp(COLOR_BACKGROUND_BLUE, COLOR_BACKGROUND_RED, t));
        board.logic(window);
        window.display();
    }
}

int main() {

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Finy - The Board Game", sf::Style::Titlebar | sf::Style::Close);
    while (window.isOpen()) {
        round(window);
    }

    return 0;
}