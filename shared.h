#ifndef BOARDGAMES_SHARED_H
#define BOARDGAMES_SHARED_H
#include "BoardGame_Classes.h"

class XO3x3 : public Board<char> {
private:
    char winner = '_';

    void init_board() {
        this->board = new char*[this->rows];
        for (int i = 0; i < this->rows; ++i) {
            this->board[i] = new char[this->columns]();
            for (int j = 0; j < this->columns; ++j) {
                this->board[i][j] = '_';
            }
        }
    }

    void delete_board() {
        for (int i = 0; i < this->rows; ++i) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }

public:

    XO3x3() {
        this->rows = 3;
        this->columns = 3;
        this->n_moves = 0;
        init_board();
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

    void display_board() override {
        for (int row = 0; row < this->rows; ++row) {
            cout << " | ";
            for (int col = 0; col < this->columns; ++col) {
                cout << this->board[col][row] << " | ";
            }
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
            delete_board();
            init_board();
            this->n_moves = 0;
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
    bool biggerBoard = true;
    XO3x3* currentBoard;
    pair<int, int> currentBoardIdx;
    XO3x3** smallerBoards = new XO3x3*[3];

    bool choose_board(int x, int y){
        if(this->smallerBoards[x][y].get_winner() == '_') {
            currentBoardIdx = make_pair(x, y);
            currentBoard = &this->smallerBoards[x][y];
            this->biggerBoard = false;
            return true;
        }
        else {
            return false;
        }
    }

    void update_status(){
        if(currentBoard->get_winner() != '_'){
            char winner = currentBoard->get_winner();
            currentBoard->display_board();
            cout << "Winner is: " << winner << endl;
            this->board[currentBoardIdx.first][currentBoardIdx.second] = winner;
            this->n_moves++;
            this->biggerBoard = true;
            return;
        }

        if (currentBoard->is_draw()){
            currentBoard->display_board();
            cout << "Draw!" << endl;
            this->biggerBoard = true;
            return;
        }

    };

    void print_smaller_board() const {
        currentBoard->display_board();
    }

    void print_ultimate_board() const {
        for (int row = 0; row < this->rows; ++row) {
            cout << " | ";
            for (int col = 0; col < this->columns; ++col) {
                cout << this->smallerBoards[col][row].get_winner() << " | ";
            }
            cout << endl;
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

// Check diagonals
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


public:
    UltimateTicTacToe(){
        this->rows = 3;
        this->columns = 3;
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

        if (this->biggerBoard){
            return choose_board(x, y);
        }
        else {
            bool success = currentBoard->update_board(x, y, symbol);
            if(success){
                update_status();
            }
            return success;
        }

    };


    void display_board() override {
        if(this->biggerBoard){
            cout << "Ultimate Tic Tac Toe Board: " << endl;
            print_ultimate_board();
        }
        else {
            cout << "Current Board (" << currentBoardIdx.first << "," << currentBoardIdx.second << "): " << endl;
            print_smaller_board();
        }
        cout << endl;
    }


    bool is_win() override {
        for (int idx = 0; idx < 3; idx++){
            if(check_win(idx)){
                return true;
            }
        }
        return false;
    }

    bool is_draw() override {
        return this->n_moves == this->rows * this->columns;
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }


};

#endif //BOARDGAMES_SHARED_H
