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
        for (int idx = 0; idx < 3; ++idx){
            if((this->board[idx][0] == this->board[idx][1] && this->board[idx][1] == this->board[idx][2] &&
                this->board[idx][0] != '_') ||
               (this->board[0][idx] == this->board[1][idx] && this->board[1][idx] == this->board[2][idx] &&
                this->board[0][idx] != '_')){
                return true;
            }
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
        if(currentBoard->is_win()){
            char winner = currentBoard->get_winner();
            cout << "Winner is: " << winner << endl;
            this->board[currentBoardIdx.first][currentBoardIdx.second] = winner;
            this->n_moves++;
            this->biggerBoard = true;
            return;
        }

        if (currentBoard->is_draw()){
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
        if((this->smallerBoards[idx][0].get_winner() == this->smallerBoards[idx][1].get_winner() && this->smallerBoards[idx][1].get_winner() == this->smallerBoards[idx][2].get_winner() &&
            this->smallerBoards[idx][0].get_winner() != '_') ||
           (this->smallerBoards[0][idx].get_winner() == this->smallerBoards[1][idx].get_winner() && this->smallerBoards[1][idx].get_winner() == this->smallerBoards[2][idx].get_winner() &&
            this->smallerBoards[0][idx].get_winner() != '_')){
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
