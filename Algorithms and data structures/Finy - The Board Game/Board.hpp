#pragma once
#include "Consts.hpp"
#include "ReactiveRectangle.hpp"
#include "WinnerBoard.hpp"
using namespace std;

struct Board {
    vector<vector<ReactiveRectangle>> cells;
    WinnerBoard winnerboard;
    GameModeBoard gameModeBoard;
    vector<pair<int, int>> marked;
    
    sf::SoundBuffer buffer;
    sf::Sound popSound;
    int pressed_idx = -1;
    int ready_to_move_idx = -1;
    int player_move = 1;
    int win = false, restart = false;
    
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
                    swap(cells[p[2*j+1]][j].isGamePieceEnemy, cells[p[2*j+1] - offset][j].isGamePieceEnemy);
                    // enemy - blue
                    //swap(cells[p[2*j]][j].isGamePiecePlayer, cells[p[2*j] + offset][j].isGamePiecePlayer);
                    return;
                }
            }
        }
    }

    void logic(sf::RenderWindow& window) {
        if (gameModeBoard.gamemode == -1) {
            gameModeBoard.logic(window);
            return;
        }
        int idx = 0;
        if (!win) {
            if (gameModeBoard.gamemode == 2 && !player_move) {
                bot_make_move(window);
                popSound.play();
                        
                pressed_idx = -1;
                player_move = !player_move;
                win = check_win();
                sf::sleep(sf::milliseconds(50));
            }
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
                        
                        popSound.play();
                        
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
        else if (win == 1)
            winnerboard.set_message("Red player won!", COLOR_RED);
        else if (win == 2)
            winnerboard.set_message("Blue player won!", COLOR_BLUE);
        
        winnerboard.logic(window);
        restart = winnerboard.retry.pressed;
    }
private:
    pair<int, int> getCoordinates(int idx) {
        return {idx / 3, idx % 3};
    }
};