#include "BoardGame_Classes.h"
#include <iostream>
#include "Players.h"

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
        return n_moves == rows * columns;
    }

    bool is_win() override {
        if (game_is_over()) {  // if the board is full
            pair<int, int> num_wins = get_wins();
            return num_wins.first > num_wins.second || num_wins.first < num_wins.second;
        }
        else {
            return false;
        }
    }

    bool is_draw() override {
        if (game_is_over()) {  // if the board is full
            pair<int, int> num_wins = get_wins();
            return num_wins.first == num_wins.second;
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


int main() {
    int choice;
    Player<char>* players[2];
    Board<char>* B = new TicTacToe5x5();
    string playerXName, player2Name;
    char Symbol[2] = {'X', 'O'};

    cout << "Welcome to FCAI X-O Game. :)\n";

    for (int i = 0; i < 2; ++i) {
        cout << "Choose Player " << Symbol[i] << " type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter Player " << Symbol[i] << " name: ";
                cin >> player2Name;
                players[i] = new HumanPlayer<char>(player2Name, Symbol[i], 5);
                break;
            case 2:
                players[i] = new SquareXORandomPlayers<char>(Symbol[i], 5);
                break;
            default:
                cout << "Invalid choice for Player " << Symbol[i] << ". Exiting the game.\n";
                return 1;
        }
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}
