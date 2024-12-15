#ifndef BOARDGAMES_SHARED_H
#define BOARDGAMES_SHARED_H
#include "BoardGame_Classes.h"

class XO3x3 : public Board<char> {
private:
    char winner = '_';

public:

    XO3x3() {
        this->rows = 3;
        this->columns = 3;
        this->n_moves = 0;
        this->board = new char*[this->rows];
        for (int i = 0; i < this->rows; ++i) {
            this->board[i] = new char[this->columns]();
            for (int j = 0; j < this->columns; ++j) {
                this->board[i][j] = '_';
            }
        }
    }

    bool update_board(int x, int y, char symbol) override {
        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) {
            return false;
        }
        if (this->board[x][y] == '_') {
            this->board[x][y] = symbol;
            this->n_moves++;
            if(is_win()){
                this->winner = symbol;
            }
            return true;
        }
        return false;
    }

    void display_board(int row)  {
            cout << "|";
            for (int col = 0; col < this->columns; ++col) {
                cout << this->board[col][row] << "|";
            }
            cout << "   ";
    }

    void display_board() override {
        for (int row = 0; row < this->rows; ++row) {
            display_board(row);
            cout << endl;
        }
    }


    bool is_win() override {
        for (int i = 0; i < this->rows; i++) {
            if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != '_') ||
                (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != '_')) {
                return true;
            }
        }

        if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != '_') ||
            (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != '_')) {
            return true;
        }

        return false;
    }

    bool is_draw() override {
        if (this->n_moves == this->rows * this->columns){
            return true;
        }
        else {
            return false;
        }
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }

    char get_winner() const {
        return this->winner;
    }

};


class UltimateTicTacToe : public Board<char> {
private:
    XO3x3* currentBoard;
    pair<int, int> currentBoardIdx;
    XO3x3** smallerBoards = new XO3x3*[3];

    bool choose_board(int x, int y){
        if(this->smallerBoards[x][y].get_winner() == '_') {
            currentBoardIdx = make_pair(x, y);
            currentBoard = &this->smallerBoards[x][y];
            return true;
        }
        else {
            return false;
        }
    }

    bool check_win(int idx){
        for (int i = 0; i < this->rows; i++) {
            if ((this->smallerBoards[idx][0].get_winner() == this->smallerBoards[idx][1].get_winner()
            && this->smallerBoards[idx][1].get_winner() == this->smallerBoards[idx][2].get_winner()
            && this->smallerBoards[idx][0].get_winner() != '_') ||
                (this->smallerBoards[0][idx].get_winner() == this->smallerBoards[1][idx].get_winner()
                && this->smallerBoards[1][idx].get_winner() == this->smallerBoards[2][idx].get_winner()
                && this->smallerBoards[0][idx].get_winner() != '_')) {
                return true;
            }
        }

        if ((this->smallerBoards[0][0].get_winner() == this->smallerBoards[1][1].get_winner()
        && this->smallerBoards[1][1].get_winner() == this->smallerBoards[2][2].get_winner()
        && this->smallerBoards[0][0].get_winner() != '_') ||
            (this->smallerBoards[0][2].get_winner() == this->smallerBoards[1][1].get_winner()
            && this->smallerBoards[1][1].get_winner() == this->smallerBoards[2][0].get_winner()
            && this->smallerBoards[0][2].get_winner() != '_')) {
            return true;
        }

        return false;
    }

    void display_ultimate(){
        cout << endl << "Ultimate Tic Tac Toe" << endl;
        for(int i = 0; i < 3; i++){
            cout << " | ";
            for(int j = 0; j < 3; j++){
                cout << this->smallerBoards[i][j].get_winner() << " | ";
            }
            cout << endl;
        }
    }


public:
    UltimateTicTacToe(){
        this->rows = 9;
        this->columns = 9;
        this->n_moves = 0;
        this->currentBoard = nullptr;
        this->board = new char*[this->rows];

        for (int i = 0; i < this->rows; ++i) {
            this->board[i] = new char[this->columns];
        }

        for (int i = 0; i < 3; ++i) {
            this->smallerBoards[i] = new XO3x3[3];
            for (int j = 0; j < 3; ++j) {
                this->smallerBoards[i][j] = XO3x3();
            }
        }

    };

    ~UltimateTicTacToe(){
        for (int i = 0; i < 3; ++i) {
            delete[] this->smallerBoards[i];
        }
        delete[] this->smallerBoards;
    };

    bool update_board(int x, int y, char symbol) override {
        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) {
            return false;
        }
        int outer_x = y / 3;
        int outer_y = x / 3;
        int inner_x = y % 3;
        int inner_y = x % 3;


        if (this->smallerBoards[outer_x][outer_y].get_winner() != '_') {
            return false;
        }
        else {
            choose_board(outer_x, outer_y);
            return this->currentBoard->update_board(inner_x, inner_y, symbol);
        }

    }

    void display_board() override {
        for (int i = 0; i < 3; i++) {
            for (int k = 0; k < 3; k++) {
                for (int j = 0; j < 3; j++) {
                    this->smallerBoards[i][j].display_board(k);
                }
                cout << endl;
            }
            cout << endl;
        }
        cout << "---------------------------" << endl;

    }

    bool is_win() override {
        for (int idx = 0; idx < 3; idx++){
            if(check_win(idx)){
                display_ultimate();
                return true;
            }
        }
        return false;
    }

    bool is_draw() override {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if(smallerBoards[i][j].get_winner() == '_' && !smallerBoards[i][j].is_draw()){
                    return false;
                }
            }
        }
        return true;
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }


};


class SusTicTacToe : public Board<char> {
private:
    // Check if a move is valid
    bool is_valid_move(int row, int col) {
        return row >= 0 && row < rows && col >= 0 && col < columns && board[row][col] == '\0';
    }

public:
    SusTicTacToe() {
        rows = 3;
        columns = 3;
        n_moves = 0;
        board = new char*[rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new char[columns]();
            for (int j = 0; j < columns; ++j) {
                board[i][j] = '\0';
            }
        }
    }

    void display_board() override {
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < columns; ++col) {
                cout << (board[col][row] == '\0' ? '.' : board[col][row]) << " ";
            }
            cout << endl;
        }
    }

    bool update_board(int row, int col, char symbol) override {
        if (is_valid_move(row, col)) {
            board[row][col] = symbol;
            n_moves++;
            return true;
        }
        return false;
    }

    bool is_win() override {
        // Check rows and columns
        for (int i = 0; i < rows; ++i) {
            if (board[i][0] == 'S' && board[i][1] == 'U' && board[i][2] == 'S') return true;
            if (board[0][i] == 'S' && board[1][i] == 'U' && board[2][i] == 'S') return true;
        }

        // Check diagonals
        if (board[0][0] == 'S' && board[1][1] == 'U' && board[2][2] == 'S') return true;
        if (board[0][2] == 'S' && board[1][1] == 'U' && board[2][0] == 'S') return true;

        return false;
    }

    bool is_draw() override {
        return n_moves == rows * columns;
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }

};


#endif //BOARDGAMES_SHARED_H
