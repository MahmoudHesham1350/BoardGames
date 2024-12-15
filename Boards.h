#ifndef BOARDGAMES_BOARDS_H
#define BOARDGAMES_BOARDS_H

#include "BoardGame_Classes.h"
#include <unordered_set>
#include <fstream>
#include <algorithm>

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
            return num_wins.first < num_wins.second;
        }
        if(n_moves == rows * columns){
            pair<int, int> num_wins = get_wins();
            return num_wins.first > num_wins.second;
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
        cout << endl;
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

    bool check_win() {
        for (int i = 0; i < this->rows; i++) {
            if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] &&
                 this->board[i][0] != '_') ||
                (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] &&
                 this->board[0][i] != '_')) {
                return true;
            }
        }

        // Check diagonals
        if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] &&
             this->board[0][0] != '_') ||
            (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] &&
             this->board[0][2] != '_')) {
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
        if (this->is_win() || this->is_draw()) {
            if (continue_game) {
                continue_game = false;
                return false;
            } else {
                return true;
            }
        }
        return false;
    }

    bool is_win() override {
        if (check_win()) {
            if (skipWin) {
                skipWin = false;
                return false;
            } else {
                return true;
            }
        }
        return false;
    }

    bool is_draw() override {
        if (this->n_moves == this->rows * this->columns + 1) {
            return true;
        } else {
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
        if (!skipWin) {
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


class PyramidTicTacToe: public Board<char> {
private:
    int last_row = -1, last_col = -1;

    // Helper function to check matches in a specific direction
    bool checkDirection(int row, int col, int dRow, int dCol) {
        char target = board[row][col];
        int count = 1;
        // Forward direction
        count += countMatches(row, col, dRow, dCol, target);
        // Backward direction
        count += countMatches(row, col, -dRow, -dCol, target);

        return count >= 3; // Winning condition
    }

    // Count matches in a direction
    int countMatches(int row, int col, int dRow, int dCol, char symbol) {
        int newRow = row + dRow, newCol = col + dCol;
        if (newRow < 0 || newRow >= rows || newCol < 0 || newCol >= columns || board[newRow][newCol] != symbol)
            return 0; // Out of bounds or no match

        return 1 + countMatches(newRow, newCol, dRow, dCol, symbol);
    }

public:
    PyramidTicTacToe() {
        // Define board dimensions
        rows = 3;
        columns = 5;

        // Allocate memory for the pyramid board
        board = new char*[rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new char[columns];
            for (int j = 0; j < columns; ++j) {
                // Initialize pyramid shape
                if (j >= columns / 2 - i && j <= columns / 2 + i)
                    board[i][j] = '-';  // Empty cell
                else
                    board[i][j] = ' ';  // Outside the pyramid
            }
        }

    }

    ~PyramidTicTacToe() {
        for (int i = 0; i < rows; ++i) {
            delete[] board[i];
        }
        delete[] board;
    }

    // Check if a player has won
    bool is_win() override {
        if (last_row == -1 || last_col == -1)
            return false;
        return checkDirection(last_row, last_col, 0, 1) || // Horizontal
               checkDirection(last_row, last_col, 1, 0) || // Vertical
               checkDirection(last_row, last_col, 1, 1) || // Diagonal (\)
               checkDirection(last_row, last_col, 1, -1);  // Diagonal (/)
    }

    void display_board() override {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                cout << (board[i][j] == '-' ? '.' : board[i][j]) << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    bool update_board(int x, int y, char symbol) override {
        if (x < 0 || x >= rows || y < columns / 2 - x || y > columns / 2 + x || board[x][y] != '-') {
            return false;
        }
        board[x][y] = symbol;
        last_row = x;
        last_col = y;
        n_moves++;
        return true;
    }

    bool is_draw() override {
        return n_moves == 9;
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }

};


class WordTicTacToe : public Board<char> {
private:
    unordered_set<string> dictionary; // Set to store valid words
    int last_row = -1, last_col = -1;

    // Check if the given word exists in the dictionary
    bool isWordValid(const string &word) {
        return dictionary.find(word) != dictionary.end();
    }

    // Recursive function to form words in a specified direction
    bool formWord(int row, int col, int dx, int dy, string &currentWord) {
        // If out of bounds or the cell is empty, stop
        if (row < 0 || col < 0 || row >= 3 || col >= 3 || this->board[row][col] == '\0') {
            return false;
        }

        // Append the current letter to the word
        currentWord += board[row][col];

        // If the word is valid, return true
        return isWordValid(currentWord);
    }

public:
    WordTicTacToe() {
        // Initialize the 3x3 board with empty cells
        rows = 3;
        columns = 3;
        loadDictionary();
        board = new char*[rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new char[columns]();
        }
    }

    void display_board() override {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                // If cell is empty, display a dot, else show the letter
                cout << (this->board[i][j] == '\0' ? '.' : this->board[i][j]) << " ";
            }
            cout << endl;
        }

        cout << endl;
    }

    // Load words from a dictionary file into the set
    void loadDictionary() {
        string filename = "dic.txt";
        ifstream file(filename);
        if (!file) {
            cerr << "Error: Could not open dictionary file!" << endl;
            exit(1);
        }

        string word;
        while (file >> word) {
            dictionary.insert(word);
        }
    }

    // Place a letter on the board and check if it forms a valid word
    bool update_board(int row, int col, char letter) override {
        if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != '\0') {
            return false;
        }
        else {
            last_row = row;
            last_col = col;
            board[row][col] = letter;
            return true;
        }

    }

    // Check if the current move forms a valid word in any direction
    bool is_win() override {
        if (last_row == - 1 || last_col == -1){
            return false;
        }
        else{
            string word = "";

            // Check horizontally
            if (formWord(last_row, 0, 0, 1, word)) return true;
            word.clear();

            // Check vertically
            if (formWord(0, last_col, 1, 0, word)) return true;
            word.clear();

            // Check diagonally (top-left to bottom-right)
            if (last_row == last_col && formWord(0, 0, 1, 1, word)) return true;
            word.clear();

            // Check diagonally (top-right to bottom-left)
            if (last_row + last_col == 2 && formWord(0, 2, 1, -1, word)) return true;

            return false;

        }


    }


    // Check if the game has ended in a draw (no valid moves left)
    bool is_draw() override {
        for (int i = 0; i < rows; ++i) {
            if (find(board[i], board[i] + columns, '\0') != board[i] + columns) {
                return false; // There's still space to play
            }
        }
        return true; // No moves left, game is a draw
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }


};



#endif //BOARDGAMES_BOARDS_H
