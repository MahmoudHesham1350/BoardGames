
#ifndef BOARDGAMES_BOARDS_H
#define BOARDGAMES_BOARDS_H
#include "BoardGame_Classes.h"

class TicTacToe5x5 : public Board<char> {
private:

    char get_symbol(int row, int col) const {
        if (row < 0 || row >= rows || col < 0 || col >= columns) {
            return ' ';
        }
        else {
            return board[row][col];
        }

    }

    pair<int, int> get_wins() const {
        pair<int, int> num_wins = {0, 0};
        for(int row = 0; row < rows; row++){
            for (int column = 0; column < columns; column++){
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
        if (row == 0 && col == columns-1){
            return true;
        }
        if (row == rows-1 && col == 0){
            return true;
        }
        if (row == rows-1 && col == columns-1){
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
        columns = 5;
        n_moves = 0;
        board = new char*[rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new char[columns]();
            for (int j = 0; j < columns; ++j) {
                board[i][j] = '_';
            }
        }

    };

    bool game_is_over() override {
        return is_win() || is_draw();
    }


    bool is_win() override {
        if (n_moves == rows * columns - 1) {
            pair<int, int> num_wins = get_wins();
            return num_wins.first > num_wins.second;
        }
        if(n_moves == rows * columns){
            pair<int, int> num_wins = get_wins();
            return num_wins.first < num_wins.second;
        }
        return false;
    }

    bool is_draw() override {
        if (n_moves == rows * columns -1){
            pair<int, int> num_wins = get_wins();
            return num_wins.first == num_wins.second;
        }
        else {
            return false;
        }
    }

    void display_board() override {
        if (n_moves == rows * columns){
            return;
        }
        for (int row = 0; row < rows; ++row) {
            cout << " | ";
            for (int col = 0; col < columns; ++col) {
                cout << board[col][row] << " | ";
            }
            cout << endl;
        }
    }

    bool update_board(int x, int y, char symbol) override {
        if (n_moves >= rows * columns - 1){
            n_moves++;
            return true;
        }
        if (x < 0 || x >= rows || y < 0 || y >= columns) {
            return false;
        }
        if (board[x][y] == '_') {
            board[x][y] = symbol;
            n_moves++;
            return true;
        }
        return false;
    }

};

class TicTacToeInverse : public Board<char> {
private:
    bool skipWin = true;
    bool continue_game = true;

    bool check_win(){
        for (int i = 0; i < this->rows; i++) {
            if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != '_') ||
                (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != '_')) {
                return true;
            }
        }

        // Check diagonals
        if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != '_') ||
            (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != '_')) {
            return true;
        }

        return false;
    }

public:
    TicTacToeInverse() {
        rows = 3;
        columns = 3;
        n_moves = 0;
        board = new char *[rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new char[columns]();
            for (int j = 0; j < columns; ++j) {
                board[i][j] = '_';
            }
        }
    }

    bool game_is_over() override {
        if (this->is_win() || this->is_draw()){
            if(continue_game){
                continue_game = false;
                return false;
            }
            else {
                return true;
            }
        }
        return false;
    }

    bool is_win() override {
        if (check_win()) {
            if(skipWin){
                skipWin = false;
                return false;
            }
            else {
                return true;
            }
        }
        return false;
    }

    bool is_draw() override {
        if (this->n_moves == this->rows * this->columns + 1) {
            return true;
        }
        else {
            return false;
        }
    }

    void display_board() override {
        for (int row = 0; row < rows; ++row) {
            cout << " | ";
            for (int col = 0; col < columns; ++col) {
                cout << board[col][row] << " | ";
            }
            cout << endl;
        }
    }

    bool update_board(int x, int y, char symbol) override {
        if (!skipWin){
            return true;
        }
        if (x < 0 || x >= rows || y < 0 || y >= columns) {
            return false;
        }
        if (board[x][y] == '_') {
            board[x][y] = symbol;
            n_moves++;
            return true;
        }
        return false;
    }



};


#endif //BOARDGAMES_BOARDS_H
