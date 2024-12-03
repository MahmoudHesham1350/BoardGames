#include "BoardGame_Classes.h"
#include <iostream>

class TicTacToe5x5 : public Board {
private:

    char get_symbol(int row, int col) const {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            return ' ';
        }
        else {
            return board[row][col];
        }

    }

    pair<int, int> get_wins() const {
        pair<int, int> num_wins = {0, 0};
        for(int row = 0; row < rows; row++){
            for (int column = 0; column < cols; column++){
                if (board[row][column] == 'X'){
                    num_wins.first+= wins(row, column, 'X');
                }
                else if (board[row][column] == 'O'){
                    num_wins.second+= wins(row, column, 'O');
                }
            }
        }
        return num_wins;
    }

    bool is_edge(int row, int col) const {
        if (row == 0 && col == 0){
            return true;
        }
        if (row == 0 && col == cols-1){
            return true;
        }
        if (row == rows-1 && col == 0){
            return true;
        }
        if (row == rows-1 && col == cols-1){
            return true;
        }
        return false;
    }

    int wins(int row, int col, char symbol) const {
        int wins_counter = 0;
        if (is_edge(row, col)){
            return wins_counter;
        }
        else {
            wins_counter += check_horizontal(row, col, symbol);
            wins_counter += check_vertical(row, col, symbol);
            wins_counter += check_diagonal(row, col, symbol);
            wins_counter += check_anti_diagonal(row, col, symbol);
            return wins_counter;
        }
    }

    bool check_horizontal(int row, int col, char symbol) const {
        return get_symbol(row-1, col) == symbol && get_symbol(row+1, col) == symbol;
    }

    bool check_vertical(int row, int col, char symbol) const {
        return get_symbol(row, col-1) == symbol && get_symbol(row, col+1) == symbol;
    }

    bool check_diagonal(int row, int col, char symbol) const {
        return get_symbol(row-1, col-1) == symbol && get_symbol(row+1, col+1) == symbol;
    }

    bool check_anti_diagonal(int row, int col, char symbol) const {
        return get_symbol(row-1, col+1) == symbol && get_symbol(row+1, col-1) == symbol;
    }



public:
    TicTacToe5x5() {
        rows = 5;
        cols = 5;
        n_moves = 0;
        board = vector<vector<char>>(rows, vector<char>(cols, '_'));
    };

    bool is_game_over() override {
        return n_moves == rows * cols;
    }

    bool is_win() override {
        if (is_game_over()) {  // if the board is full
            pair<int, int> num_wins = get_wins();
            return num_wins.first > num_wins.second || num_wins.first < num_wins.second;
        }
        else {
            return false;
        }
    }

    bool is_draw() override {
        if (is_game_over()) {  // if the board is full
            pair<int, int> num_wins = get_wins();
            return num_wins.first == num_wins.second;
        }
        else {
            return false;
        }
    }

    void display_board() override {
        for (const vector <char>& row : board) {
            cout << " | ";
            for (const char& cell : row) {
                cout << cell << " | ";
            }
            cout << endl;
        }
    }

};



int main() {
    return 0;
}
