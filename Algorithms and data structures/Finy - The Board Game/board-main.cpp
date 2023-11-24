
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

using namespace std;

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


struct ReactiveRectangle : sf::RectangleShape {

    bool pressed = false;
    bool isGamePiecePlayer = false;
    bool isGamePieceEnemy = false;
    bool hint = false;
    
    void logic(sf::RenderWindow& window, int player_move) {
        pressed |= onTap(window);
        this->setFillColor( this->hint ? COLOR_GREEN :
            isGamePiecePlayer ? player_move ?
                pressed ? COLOR_BLUE_PRESS : COLOR_BLUE
                : COLOR_BLUE
            : isGamePieceEnemy ? !player_move ?
                    pressed ? COLOR_RED_PRESS : COLOR_RED
                    : COLOR_RED
                : pressed ? COLOR_BASIC_PRESS : COLOR_BASIC);
    }
    
    bool onTap(sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f rectPos = this->getPosition();
        sf::Vector2f rectSize = this->getSize();
        return (mousePos.x >= rectPos.x && mousePos.x <= rectPos.x + rectSize.x &&
                mousePos.y >= rectPos.y && mousePos.y <= rectPos.y + rectSize.y &&
                sf::Mouse::isButtonPressed(sf::Mouse::Left));
    }
};

struct RetryRectangle : ReactiveRectangle {
    sf::Text label; sf::Font font;
    RetryRectangle() {
        this->setPosition(122, SCREEN_HEIGHT * 0.4 + 100);
        this->setFillColor(COLOR_BACKGROUND);
        this->setSize({CELL_WIDTH, CELL_WIDTH / 2});
        this->setOutlineThickness(CELL_OUTLINE);
        this->setOutlineColor(sf::Color::Black);
        this->label.setPosition(this->getPosition().x + 6, this->getPosition().y + 2);
        this->label.setOutlineColor(sf::Color::Black);
        this->label.setOutlineThickness(2.0);
        this->font.loadFromFile("Matias Webfont.ttf");
        this->label.setFont(font);
        this->label.setLetterSpacing(2.5);
        this->label.setCharacterSize(20);
        this->label.setFillColor(sf::Color::White);
        this->label.setString("Retry");
    }
    void logic(sf::RenderWindow& window, int& restart) {
        pressed |= onTap(window);
        this->setFillColor(
            pressed ? COLOR_BLUE_PRESS : COLOR_BACKGROUND
        );
        restart = pressed;
        window.draw(*this);
        window.draw(label);
    }
};

struct WinnerBoard : sf::RectangleShape {
    sf::Text label; sf::Font font; bool draw = false; RetryRectangle retry;
    WinnerBoard() {        
        this->setFillColor(COLOR_BASIC_PRESS);
        this->setSize({CELL_WIDTH * 4, CELL_WIDTH * 2.45});
        this->setPosition({32, SCREEN_HEIGHT * 0.4});
        this->setOutlineColor(sf::Color::Black);
        this->setOutlineThickness(CELL_OUTLINE);
        this->label.setPosition(this->getPosition().x + 10, this->getPosition().y + 50);
        this->label.setOutlineColor(sf::Color::Black);
        this->label.setOutlineThickness(3.0);
        this->font.loadFromFile("Matias Webfont.ttf");
        this->label.setFont(font);
        this->label.setLetterSpacing(2.5);
        this->label.setCharacterSize(30);
    }
    void set_message(string message, sf::Color message_color) {
        this->label.setString(message);
        message_color.a = 255;
        this->label.setColor(message_color);
        this->label.setFillColor(message_color);
        draw = true;
    }
    void logic(sf::RenderWindow& window, int& restart) {
        if (this->draw) {
            window.draw(*this);
            window.draw(label);
            retry.logic(window, restart);
        }
    }
};

pair<int, int> getCoordinates(int idx) {
    return {idx / 3, idx % 3};
}

struct Board {
    vector<vector<ReactiveRectangle>> cells;
    WinnerBoard winnerboard; //playmodeboard
    vector<pair<int, int>> marked;
    int pressed_idx = -1;
    int ready_to_move_idx = -1;
    int player_move = 1;
    int win = false, restart = false;
    
    Board() {
        cells.resize(8, vector<ReactiveRectangle>(3));
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 3; ++j) {
                ReactiveRectangle cell;
                cell.setFillColor(COLOR_BASIC);
                cell.setSize({CELL_WIDTH, CELL_WIDTH});
                cell.setPosition({50 + CELL_OFFSET * j, 50 + CELL_OFFSET * i});
                cell.setOutlineColor(sf::Color::Black);
                cell.setOutlineThickness(CELL_OUTLINE);
                cells[i][j] = cell;
            }
        }

        for (int idx : {2, 4, 6}) {
            pair<int, int> p = getCoordinates(idx);
            cells[p.first][p.second].isGamePiecePlayer = true;
        }
        
        for (int idx : {15, 19, 23}) {
            pair<int, int> p = getCoordinates(idx);
            cells[p.first][p.second].isGamePieceEnemy = true;
        }
    }
    void get_positions() {
        vector<int> positions(6);
        for (int j = 0; j < 3; ++j) {
            int idx1 = 0, idx2 = 7;
            while (!cells[idx1][j].isGamePiecePlayer)
                idx1++;
            while (!cells[idx2][j].isGamePieceEnemy)
                idx2--;
            positions.push_back(idx1);
            positions.push_back(idx2);
        }
        
    }
    
    int check_win() {
        // LazyWin
        /*for (int j = 0; j < 3; ++j) {
            int idx1 = 0, idx2 = 7;
            while (!cells[idx1][j].isGamePiecePlayer)
                idx1++;
            while (!cells[idx2][j].isGamePieceEnemy)
                idx2--;
            if (idx2 - idx1 != 1)
                return false;
        }
        return player_move ? 1 : 2;*/
        
        // NerdWin
        if (cells[6][0].isGamePiecePlayer && cells[6][1].isGamePiecePlayer && cells[6][2].isGamePiecePlayer)
            return 2;
        if (cells[1][0].isGamePieceEnemy && cells[1][1].isGamePieceEnemy && cells[1][2].isGamePieceEnemy)
            return 1;
        return 0;
    }

    void logic(sf::RenderWindow& window) {
        int idx = 0;
        if (!win) {
            for (auto& row : cells)
                for_each(row.begin(), row.end(), [&](ReactiveRectangle& cell) {
                    cell.pressed = (idx == pressed_idx);
                    cell.logic(window, player_move);
                    if (cell.pressed)
                        pressed_idx = idx;
                    
                    if ((cell.isGamePieceEnemy || cell.isGamePiecePlayer) && cell.pressed) {
                        ready_to_move_idx = idx;   
                    }
                    
                    pair<int, int> a = getCoordinates(ready_to_move_idx);
                    pair<int, int> b = getCoordinates(idx);
                    if (cells[b.first][b.second].hint && ((cells[a.first][a.second].isGamePieceEnemy && !player_move) || (cells[a.first][a.second].isGamePiecePlayer && player_move))
                    && !cell.isGamePieceEnemy && !cell.isGamePiecePlayer && cell.pressed && ready_to_move_idx != -1 && a.second == b.second) {
                        player_move ?
                            swap(cells[a.first][a.second].isGamePiecePlayer, cells[b.first][b.second].isGamePiecePlayer)
                            :swap(cells[a.first][a.second].isGamePieceEnemy, cells[b.first][b.second].isGamePieceEnemy);
                        pressed_idx = -1;
                        player_move = !player_move;
                        win = check_win();
                        
                        for (auto& [i, j] : marked)
                            cells[i][j].hint = false;
                        marked.clear();
                        sf::sleep(sf::milliseconds(50));
                    }
                    
                    if (cell.pressed && ((cell.isGamePieceEnemy && !player_move) || (cell.isGamePiecePlayer && player_move))) {
                        for (auto& [i, j] : marked)
                            cells[i][j].hint = false;

                        marked.clear();
                        for (int i = b.first - 1; i >= 0; --i) {
                            if (cells[i][b.second].isGamePieceEnemy || cells[i][b.second].isGamePiecePlayer)
                                break;
                            marked.push_back({i, b.second});
                        }
                        for (int i = b.first + 1; i < 8; ++i) {
                            if (cells[i][b.second].isGamePieceEnemy || cells[i][b.second].isGamePiecePlayer)
                                break;
                            marked.push_back({i, b.second});
                        }

                        for (auto& [i, j] : marked)
                            cells[i][j].hint = true;
                    }

                    window.draw(cell);
                    idx++;
                });
        }
        else if (win == 1) {
            for (auto& row : cells)
            for_each(row.begin(), row.end(), [&](ReactiveRectangle& cell) {cell.setFillColor(COLOR_RED); window.draw(cell);});
            winnerboard.set_message("Red player won!", COLOR_RED);
        }
        else if (win == 2) {
            for (auto& row : cells)
            for_each(row.begin(), row.end(), [&](ReactiveRectangle& cell) {cell.setFillColor(COLOR_BLUE); window.draw(cell);});
            winnerboard.set_message("Blue player won!", COLOR_BLUE);
        }
        
        winnerboard.logic(window, restart);
    }
};
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

        board.player_move ? t = max(0.0, t - 0.0025) : t = min(1.0, t + 0.0025);
        window.clear(lerp(COLOR_BACKGROUND_BLUE, COLOR_BACKGROUND_RED, t));
        board.logic(window);
        window.display();
    }
}

bool dfs(bool me, int a, int b, int c, int d, int e, int f, vector<pair<char, int>> moves, map<tuple<int, int, int, int, int, int>, int>& dp) {
    auto it = dp.find({a,b,c,d,e,f});
    if (it != dp.end())
        return it->second;

    if ((a - b == 0) && (c - d == 0) && (e - f == 0)) {
        cout << "\n" << (me ? "bot" : "player") << "\n";
        for (pair<char, int> p : moves) {
            cout << p.first << " " << p.second << "       ";
        }
        cout << "\n\n";
        return dp[{a,b,c,d,e,f}] = me;
    }
        
    if (me) {
        bool ok = true;
        for (int i = a; i < b; ++i) {
            moves.push_back({'a', i - a});
            ok = !dfs(!me, i,b,c,d,e,f, moves, dp);
            moves.pop_back();
            if (!ok)
                return dp[{a,b,c,d,e,f}] = !me;
        }
        for (int i = c; i < d; ++i) {
            moves.push_back({'c', i - c});
            ok = !dfs(!me, a,b,i,d,e,f, moves, dp);
            moves.pop_back();
            if (!ok)
                return dp[{a,b,c,d,e,f}] = !me;
        }
        for (int i = e; i < f; ++i) {
            moves.push_back({'e', i - e});
            ok = !dfs(!me, a,b,c,d,i,f, moves, dp);
            moves.pop_back();
            if (!ok)
                return dp[{a,b,c,d,e,f}] = !me;
        }
        // то есть если после хода бота игрок ни одним способом не побеждает - это правильный ход
        return dp[{a,b,c,d,e,f}] = me;
        //return !dfs(!me, a + 1,b,c,d,e,f) && !dfs(!me, a,b,c+1,d,e,f) && !dfs(!me, a,b,c,d,e+1,f);
    }
    else {
        bool ok = true;
        for (int i = b; b > a; --i) {
            moves.push_back({'b', i - b});
            ok = !dfs(!me, a,i,c,d,e,f, moves, dp);
            moves.pop_back();
            if (!ok)
                return dp[{a,b,c,d,e,f}] = me;
        }
        for (int i = d; d > c; --i) {
            moves.push_back({'d', i - d});
            ok = !dfs(!me, a,b,c,i,e,f, moves, dp);
            moves.pop_back();
            if (!ok)
                return dp[{a,b,c,d,e,f}] = me;
        }
        for (int i = f; f > e; --i) {
            moves.push_back({'f', i - f});
            ok = !dfs(!me, a,b,c,d,e,i, moves, dp);
            moves.pop_back();
            if (!ok)
                return dp[{a,b,c,d,e,f}] = me;
        }
        // то есть если после хода бота игрок ни одним способом не побеждает - это правильный ход
        return dp[{a,b,c,d,e,f}] = !me;
    }


    //else {

        // если это игрок, то он побеждает если хотя бы один его вариант приведет к победе
        // или если любой следующий ход врага не даст победы
    //}
    //return !dfs(!me, a + 1,b,c,d,e,f) || !dfs(!me, a,b,c+1,d,e,f) || !dfs(!me, a,b,c,d,e+1,f);
}

int main() {
    /*const bool bot = 1;
    const bool player = 0;

    vector<pair<char, int>> moves;
    map<tuple<int, int, int, int, int, int>, int> dp;
    cout << dfs(bot, 2, 4, 6, 15, 19, 23, moves, dp) << endl;
    cout << dfs(player, 2, 4, 6, 15, 19, 23, moves, dp) << endl;
    */
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Finy - The Board Game", sf::Style::Titlebar | sf::Style::Close);
    while (window.isOpen()) {
        round(window);
    }

    return 0;
}