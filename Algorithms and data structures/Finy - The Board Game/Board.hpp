#pragma once
#include "Consts.hpp"
#include "ReactiveRectangle.hpp"
#include "WinnerBoard.hpp"
using namespace std;

struct Board {
    struct SmoothMoveAnimator {
        bool isMoving = false;
        int row, from, to;
        sf::Clock startTimeStamp;
    };
    SmoothMoveAnimator moveAnimator;
    vector<vector<ReactiveRectangle>> cells;
    WinnerBoard winnerboard;
    GameModeBoard gameModeBoard;
    vector<pair<int, int>> marked;
    
    sf::SoundBuffer buffer;
    sf::Sound popSound;
    int pressed_idx = -1;
    int ready_to_move_idx = -1;
    int player_move = 1;
    int win = false, restart = false, set_once = false;
    
    Board() {
        buffer.loadFromFile("long-pop.wav");
        popSound.setBuffer(buffer);
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

    void logic(sf::RenderWindow& window) {
        if (gameModeBoard.gamemode == -1) {
            gameModeBoard.logic(window);
            return;
        }
        if (!win)
            play_the_game(window);
        else if (!set_once) {
            set_once = true;
            sf::sleep(sf::milliseconds(1000));
            winnerboard.set_message(win == 1 ? "Red player won!" : "Blue player won!"
                                    , win == 1 ? COLOR_RED : COLOR_BLUE);
        }
        
        winnerboard.logic(window);
        restart = winnerboard.retry.pressed;
    }

    void play_the_game(sf::RenderWindow& window) {
        if (moveAnimator.isMoving) {
            if (moveAnimator.startTimeStamp.getElapsedTime().asMilliseconds() > 60) {
                moveAnimator.startTimeStamp.restart();
                // with this buttons change colors mid animation
                for (auto& row : cells)
                    for (ReactiveRectangle& cell : row) {
                        cell.pressed = false;
                        cell.logic(window, player_move);
                    }
                move_process();
            }
        }
        else {
            if (gameModeBoard.gamemode == 2 && !player_move)
                enemy_logic(window);
            else player_logic(window);
        }
        for (auto& row : cells)
            for (ReactiveRectangle& cell : row)
                window.draw(cell);
    }
    
    // Enemy and Player
    
    void enemy_logic(sf::RenderWindow& window) {
        sf::sleep(sf::milliseconds(1000));
        bot_make_move(window);
    }    

    void player_logic(sf::RenderWindow& window) {
        int idx = 0;
        for (auto& row : cells)
            for (ReactiveRectangle& cell : row) {
                cell.pressed = (idx == pressed_idx);
                cell.logic(window, player_move);
                if (cell.pressed) {
                    pressed_idx = idx;
                    if (cell.isGamePieceEnemy || cell.isGamePiecePlayer)
                        ready_to_move_idx = idx;
                }   
                auto [a, b] = getCoordinates(ready_to_move_idx);
                bool needHints = cell.pressed && ((cell.isGamePieceEnemy && !player_move) || (cell.isGamePiecePlayer && player_move));
                if (needHints)
                    add_hints(a, b);

                if (ready_to_move_idx == idx) {
                    idx++;
                    continue;
                }
                    
                auto [x, y] = getCoordinates(idx);
                bool moveBelongsToPlayer = ((cells[a][b].isGamePieceEnemy && !player_move) || (cells[a][b].isGamePiecePlayer && player_move));
                bool moveToEmptyCell = !cell.isGamePieceEnemy && !cell.isGamePiecePlayer;
                bool sameRow = b == y;

                if (moveBelongsToPlayer && moveToEmptyCell && cells[x][y].hint && cell.pressed && ready_to_move_idx != -1 && sameRow)
                    init_smooth_moveAnimation(a, x, b);
                
                idx++;
            }
    }



// maybe add option to choose who to play vs bot
// perfect state
private:
    void add_hints(int x, int y) {
        for (auto& [i, j] : marked)
            cells[i][j].hint = false;

        marked.clear();
        for (int i = x - 1; i >= 0; --i) {
            if (cells[i][y].isGamePieceEnemy || cells[i][y].isGamePiecePlayer)
                break;
            marked.push_back({i, y});
        }
        for (int i = x + 1; i < 8; ++i) {
            if (cells[i][y].isGamePieceEnemy || cells[i][y].isGamePiecePlayer)
                break;
            marked.push_back({i, y});
        }

        for (auto& [i, j] : marked)
            cells[i][j].hint = true;
    }
    vector<int> get_positions() {
        vector<int> positions;
        for (int j = 0; j < 3; ++j) {
            int idx1 = 0, idx2 = 7;
            while (!cells[idx1][j].isGamePiecePlayer)
                idx1++;
            while (!cells[idx2][j].isGamePieceEnemy)
                idx2--;
            positions.push_back(idx1);
            positions.push_back(idx2);
        }
        return positions;
    }
    
    bool LazyWin() {
        for (int j = 0; j < 3; ++j) {
            int idx1 = 0, idx2 = 7;
            while (!cells[idx1][j].isGamePiecePlayer)
                idx1++;
            while (!cells[idx2][j].isGamePieceEnemy)
                idx2--;
            if (idx2 - idx1 != 1)
                return false;
        }
        return player_move ? 1 : 2;
    }
    int check_win() {
        // LazyWin
        
        // NerdWin
        if (cells[6][0].isGamePiecePlayer && cells[6][1].isGamePiecePlayer && cells[6][2].isGamePiecePlayer)
            return 2;
        if (cells[1][0].isGamePieceEnemy && cells[1][1].isGamePieceEnemy && cells[1][2].isGamePieceEnemy)
            return 1;
        return 0;
    }
    pair<int, int> getCoordinates(int idx) {
        return {idx / 3, idx % 3};
    }

    void bot_make_move(sf::RenderWindow& window) {
        vector<int> p = get_positions();
        int dist1 = abs(p[0] - p[1]) - 1, dist2 = abs(p[2] - p[3]) - 1, dist3 = abs(p[4] - p[5]) - 1;
        string cur = to_string(dist1) + to_string(dist2) + to_string(dist3);
        // assume bot is top player
        sort(cur.begin(), cur.end());
        set<string> bad = {
            "000",
            "011",
            "022",
            "033",
            "044",
            "123",
            "134",
            "145",
            "246"};
        for (int j = 0; j < 3; ++j) {
            string node = cur;
            while (node[j] > '0') {
                node[j]--;
                string buf = node;
                sort(buf.begin(), buf.end());
                if (bad.find(buf) != bad.end()) {
                    int offset = cur[j] - node[j];
                    if (dist1 == cur[j] - '0') j = 0;
                    else if (dist2 == cur[j] - '0') j = 1;
                    else j = 2;
                    // enemy - red
                    init_smooth_moveAnimation(p[2*j+1], p[2*j+1]-offset, j);
                    
                    // enemy - blue
                    //init_smooth_moveAnimation(p[2*j], p[2*j]+offset, j);
                    return;
                }
            }
        }
    }

    void after_move_cleanup() {
        pressed_idx = -1;
        player_move = !player_move;
        for (auto& [i, j] : marked)
            cells[i][j].hint = false;
        marked.clear();
    }
    void swap_em(int a, int b, int x, int y) {
        swap(cells[a][b].isGamePiecePlayer, cells[x][y].isGamePiecePlayer);
        swap(cells[a][b].isGamePieceEnemy, cells[x][y].isGamePieceEnemy);
    }
    void move_process() {
        auto& [isMoving, row, from, to, timeStamp] = moveAnimator;
        if (from == to) {
            isMoving = false;
            win = check_win();
        }
        else {
            // to Up
            if (from > to) {
                swap_em(from, row, from-1, row);
                from--;
            } else {
                swap_em(from, row, from+1, row);
                from++;
            }
        }
    }
    void init_smooth_moveAnimation(int from, int to, int row) {
        popSound.play();
        moveAnimator.startTimeStamp.restart();
        moveAnimator.isMoving = true;
        moveAnimator.from = from; moveAnimator.to = to;
        moveAnimator.row = row;
        after_move_cleanup();
    }
};