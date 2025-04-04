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
        if (this->n_moves == this->rows * this->columns && !check_win()) {
            return true;
        } else {
            return false;
        }
    }

    void display_board() override {
        if (!skipWin) {
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
    string currentWord;

    // Check if the given word exists in the dictionary
    bool isWordValid() {
        return dictionary.find(currentWord) != dictionary.end();
    }

    // Recursive function to form words in a specified direction
    void formWord(int row, int col, int dx, int dy) {
        // If out of bounds or the cell is empty, stop
        if (row < 0 || col < 0 || row >= 3 || col >= 3 || this->board[row][col] == '\0') {
            return;
        }
        else {
            // Append the current letter to the word
            currentWord += board[row][col];
            formWord(row + dx, col + dy, dx, dy);
        }
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
            transform(word.begin(), word.end(), word.begin(), [](char c) {
                return toupper(c);
            });

            dictionary.insert(word);
        }
    }

    // Place a letter on the board and check if it forms a valid word
    bool update_board(int row, int col, char letter) override {
        if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[col][row] != '\0') {
            return false;
        }
        else {
            board[col][row] = letter;
            return true;
        }

    }


    // Check if the current move forms a valid word in any direction
    bool is_win() override {
        // Check horizontally
        for (int i = 0; i < rows; ++i) {
            formWord(i, 0, 0, 1);
            if (isWordValid()) return true;
            this->currentWord.clear();
        }

        // Check in reverse horizontally
        for (int i = 0; i < rows; ++i) {
            formWord(i, 2, 0, -1);
            if (isWordValid()) return true;
            this->currentWord.clear();
        }

        // Check vertically
        for (int i = 0; i < columns; ++i) {
            formWord(0, i, 1, 0);
            if (isWordValid()) return true;
            this->currentWord.clear();
        }

        // Check in reverse vertically
        for (int i = 0; i < columns; ++i) {
            formWord(2, i, -1, 0);
            if (isWordValid()) return true;
            this->currentWord.clear();
        }

        // Check diagonally (top-left to bottom-right)
            formWord(0, 0, 1, 1);
            if (isWordValid()) return true;
            this->currentWord.clear();

        // Check diagonally (top-right to bottom-left)
            formWord(0, 2, 1, -1);
            if (isWordValid()) return true;
            this->currentWord.clear();

        // Check diagonally (bottom-right to top-left)
            formWord(2, 2, -1, -1);
            if (isWordValid()) return true;
            this->currentWord.clear();

        // Check diagonally (bottom-left to top-right)
            formWord(2, 0, -1, 1);
            if (isWordValid()) return true;
            this->currentWord.clear();

        return false;





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


class NumbersOX : public Board<char> {

public:

    NumbersOX() {
        rows = 3;
        columns = 3;
        n_moves = 0;
        board = new char *[rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new char[columns]();
            for (int j = 0; j < columns; ++j) {
                board[i][j] = '0';
            }
        }
    }

    void display_board() override {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (board[j][i] == '0') {
                    cout << " . ";
                } else {
                    cout << " " << board[j][i] << " ";
                }
            }
            cout << "\n";
        }
        cout << "\n";
    }

    bool update_board(int x, int y, char number) override {
        if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] != '0') {
            return false;
        }
        if (number < '1' || number > '9') {
            return false;
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (board[i][j] == number) {
                    return false;
                }
            }
        }
        board[x][y] = number;
        n_moves++;
        return true;
    }

    // Function to check if there's a winner
    bool is_win() override {
    // Check rows and columns
    for (int i = 0; i < rows; i++) {
        if (board[i][0] - '0' + board[i][1] - '0' + board[i][2] - '0' == 15 &&
            board[i][0] != '0' && board[i][1] != '0' && board[i][2] != '0') {
            return true;
        }
        if (board[0][i] - '0' + board[1][i] - '0' + board[2][i] - '0' == 15 &&
            board[0][i] != '0' && board[1][i] != '0' && board[2][i] != '0') {
            return true;
        }
    }

    // Check diagonals
    if (board[0][0] - '0' + board[1][1] - '0' + board[2][2] - '0' == 15 &&
        board[0][0] != '0' && board[1][1] != '0' && board[2][2] != '0') {
        return true;
    }
    if (board[0][2] - '0' + board[1][1] - '0' + board[2][0] - '0' == 15 &&
        board[0][2] != '0' && board[1][1] != '0' && board[2][0] != '0') {
        return true;
    }

    return false;
}

    bool is_draw() override {
        return n_moves == rows * columns;
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }

};

// Board implementation for Four-in-a-Row
class FourInARowBoard : public Board<char> {
public:
    FourInARowBoard(int r = 6, int c = 7) {
        rows = r;
        columns = c;
        board = new char*[rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new char[columns];
            fill(board[i], board[i] + columns, '.'); // Initialize empty grid
        }
    }

    // Update the board with the player's move
    bool update_board(int x, int y, char symbol) override {
        if (y < 0 || y >= columns || board[0][y] != '.') return false;

        for (int i = rows - 1; i >= 0; --i) {
            if (board[i][y] == '.') {
                board[i][y] = symbol;
                n_moves++;
                return true;
            }
        }
        return false;
    }

    // Display the current state of the board
    void display_board() override {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        for (int j = 0; j < columns; ++j) cout << j << " "; // Column numbers
        cout << "\n\n";
    }

    // Check for a winner
    bool is_win() override {
        return check_horizontal() || check_vertical() || check_diagonal();
    }

    // Check if all moves are done (draw)
    bool is_draw() override {
        return n_moves == rows * columns && !is_win();
    }

    // Check if the game is over
    bool game_is_over() override {
        return is_win() || is_draw();
    }

private:
    bool check_horizontal() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j <= columns - 4; ++j) {
                if (board[i][j] != '.' && board[i][j] == board[i][j + 1] &&
                    board[i][j] == board[i][j + 2] && board[i][j] == board[i][j + 3])
                    return true;
            }
        }
        return false;
    }

    bool check_vertical() {
        for (int i = 0; i <= rows - 4; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (board[i][j] != '.' && board[i][j] == board[i + 1][j] &&
                    board[i][j] == board[i + 2][j] && board[i][j] == board[i + 3][j])
                    return true;
            }
        }
        return false;
    }

    bool check_diagonal() {
        // Check for diagonals (\ direction)
        for (int i = 0; i <= rows - 4; ++i) {
            for (int j = 0; j <= columns - 4; ++j) {
                if (board[i][j] != '.' && board[i][j] == board[i + 1][j + 1] &&
                    board[i][j] == board[i + 2][j + 2] && board[i][j] == board[i + 3][j + 3])
                    return true;
            }
        }
        // Check for diagonals (/ direction)
        for (int i = 0; i <= rows - 4; ++i) {
            for (int j = 3; j < columns; ++j) {
                if (board[i][j] != '.' && board[i][j] == board[i + 1][j - 1] &&
                    board[i][j] == board[i + 2][j - 2] && board[i][j] == board[i + 3][j - 3])
                    return true;
            }
        }
        return false;
    }
};

#endif //BOARDGAMES_BOARDS_H
