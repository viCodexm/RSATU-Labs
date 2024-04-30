
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void print(vector<vector<int>>& board) {
    cout << "\nДоска:\n";
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            if ((j + i) & 1)
                cout << "\033[40m";
            else cout << "\033[107m";
            cout << setw(3) << board[i][j] << " ";
        }
        cout << "\n";
    }
}

int knight_moves[][2] = {
    {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2},
    {-1,  2}, { 2, -1}, { 1, 2}, { 2, 1}
};

bool possible(int x, int y, int n, vector<vector<int>>& board) {
    return 0 <= x && x < n && 0 <= y && y < n && !board[x][y];
}

long long count = 0;
bool find_path(int cur_x, int cur_y, int move, vector<vector<int>>& board, int maxsize) {
    count++;
    board[cur_x][cur_y] = move;
    if (move >= maxsize)
        return 1;
    //print(board);
    for (int i = 0; i < 8; ++i) {
        int next_x = cur_x + knight_moves[i][0];
        int next_y = cur_y + knight_moves[i][1];
        if (possible(next_x, next_y, board.size(), board)
        && find_path(next_x, next_y, move + 1, board, maxsize))
            return 1;
    }
    board[cur_x][cur_y] = 0;
    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);
    int n; cout << "Введите n: "; cin >> n;
    int x, y; cout << "Введите x и y: "; cin >> x >> y;
    vector<vector<int>> board(n, vector<int>(n, 0));

    //freopen("output.txt", "w", stdout);
    //print(board);
    if (find_path(x, y, 1, board, n * n)) {
        cout << "Путь найден\n";
        print(board);
    }
    else cout << "Путь не найден\n";

    cout << "\n\ncount: " << count;
    return 0;
}