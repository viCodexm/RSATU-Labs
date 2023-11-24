
#include <SFML/Graphics.hpp>

using namespace std;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int CELL_WIDTH = 60, CELL_OUTLINE = 4, CELL_OFFSET = CELL_WIDTH + CELL_OUTLINE * 3;
const sf::Color COLOR_BACKGROUND(120, 120, 120), COLOR_LIGHT(50, 50, 50),
            COLOR_BASIC(150, 150, 150), COLOR_BASIC_PRESS = COLOR_BASIC + COLOR_LIGHT,
            COLOR_BLUE(150, 150, 220), COLOR_BLUE_PRESS = COLOR_BLUE + COLOR_LIGHT;
            


struct ReactiveRectangle : sf::RectangleShape {

    bool pressed = false;
    float speed = 0.05;
    int offset = 0;
    
    void standart_logic(sf::RenderWindow& window) {
        pressed = onTap(window);
        this->setFillColor(
            pressed ? COLOR_BASIC_PRESS : COLOR_BASIC
        );
    }
    void jumping_logic(sf::RenderWindow& window) {
        standart_logic(window);
        this->setFillColor(
            pressed ? COLOR_BLUE_PRESS : COLOR_BLUE
        );
    }
    
    bool onTap(sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f rectPos = this->getPosition();
        sf::Vector2f rectSize = this->getSize();
        return (mousePos.x >= rectPos.x && mousePos.x <= rectPos.x + rectSize.x &&
                mousePos.y >= rectPos.y && mousePos.y <= rectPos.y + rectSize.y &&
                sf::Mouse::isButtonPressed(sf::Mouse::Left));
    }
    void shake() {
        offset++;
        this->move(0.0f, speed);
        const int border = 200;
        if (offset > border) {
            speed = -speed;
            offset = -border;
        }
    }
};

struct Board {
    vector<ReactiveRectangle> cells;
    int prev_pressed_idx = -1;
    int jumping_idx = 0;
    bool animation = false;
    sf::Clock animation_start;
    
    Board(const int n, const int m) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                ReactiveRectangle cell;
                cell.setFillColor(COLOR_BASIC);
                cell.setSize({CELL_WIDTH, CELL_WIDTH});
                cell.setPosition({50 + CELL_OFFSET * j, 50 + CELL_OFFSET * i});
                cell.setOutlineColor(sf::Color::Black);
                cell.setOutlineThickness(CELL_OUTLINE);
                cells.push_back(cell);
            }
        }
        redistribute();
    }
    void redistribute() {
        int idx = 0, jumping_idx = rand() % cells.size();
    }
    void logic(sf::RenderWindow& window) {
        int idx = 0;
        for (ReactiveRectangle& cell : cells) {

            if (idx == jumping_idx) {
                
                cell.jumping_logic(window);
                if (cell.pressed && prev_pressed_idx == -1) {
                    animation = true;
                    animation_start.restart();
                    prev_pressed_idx = idx;
                }
                if (animation) {
                    cell.shake();
                    if (animation_start.getElapsedTime().asSeconds() > 1 && cell.offset == 0) {
                        animation = false;
                        jumping_idx = rand() % cells.size();
                    }
                }
            } else {
                cell.standart_logic(window);
                if (cell.pressed && !animation && prev_pressed_idx == -1) {
                    jumping_idx = rand() % cells.size();
                    prev_pressed_idx = idx;
                }
            }
             

            
            window.draw(cell);
            idx++;
        };
    }
};

int main() {

    Board board(4, 4);
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), L"Кнопки", sf::Style::Titlebar | sf::Style::Close);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                board.prev_pressed_idx = -1;
        }
        window.clear(COLOR_BACKGROUND);
        board.logic(window);
        window.display();
    }

    return 0;
}