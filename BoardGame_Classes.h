#include <vector>
#include <string>

using namespace std;

class Board{
protected:
    int rows;
    int cols;
    vector<vector<char>> board;
    int n_moves;

public:
    template <typename T>
    bool update_board(int row, int col, T symbol) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            return false;
        }
        board[row][col] = symbol;
        n_moves++;
        return true;
    };

    void virtual display_board() = 0;

    bool virtual is_win() = 0;
    bool virtual is_draw() = 0;
    bool virtual is_game_over() {
        return is_win() || is_draw();
    };

};

class Player{
protected:
    string name;
    char symbol;
    Board* boardPtr;

public:
    Player(string name, char symbol, Board* boardPtr) {
        this->name = name;
        this->symbol = symbol;
        this->boardPtr = boardPtr;
    };

    bool virtual getMove(int& row, int& col) = 0;

    char getSymbol() {
        return symbol;
    };

    string getName() {
        return name;
    };

    void setBoard(Board* ptrToBoard) {
        this->boardPtr = ptrToBoard;
    };
};

class GameManger{
private:
    Board* boardPtr;
    pair<Player*, Player*> players;

public:
    void run(){}
};
