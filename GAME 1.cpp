#include <iostream>
#include <vector>
using namespace std;

// Template function for displaying the board
template <typename T>
void displayBoard(const vector<vector<T>> &board) {
    for (const auto &row : board) {
        for (const auto &cell : row) {
            cout << (cell == '-' ? '.' : cell) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

class PyramidTicTacToe {
private:
    vector<vector<char>> board;
    char currentPlayer;

    // Check if a player has won
    bool isWinningMove(int row, int col) {
        return checkDirection(row, col, 0, 1) || // Horizontal
               checkDirection(row, col, 1, 0) || // Vertical
               checkDirection(row, col, 1, 1) || // Diagonal (\)
               checkDirection(row, col, 1, -1);  // Diagonal (/)
    }

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
    int countMatches(int row, int col, int dRow, int dCol, char target) {
        int newRow = row + dRow, newCol = col + dCol;
        if (newRow < 0 || newRow >= board.size() || newCol < 0 || newCol >= board[newRow].size())
            return 0; // Out of bounds
        if (board[newRow][newCol] != target)
            return 0; // No match

        return 1 + countMatches(newRow, newCol, dRow, dCol, target);
    }

public:
    PyramidTicTacToe() : board{{' ',' ', '-'},  {' ','-', '-', '-'}, {'-', '-', '-', '-', '-'}}, currentPlayer('X') {}

    // Make a move on the board
    bool playMove(int row, int col) {
        if (row < 0 || row >= board.size() || col < 0 || col >= board[row].size() || board[row][col] != '-') {
            cout << "Invalid move! Try again.\n";
            return false; // Invalid move
        }

        // Place the current player's mark
        board[row][col] = currentPlayer;

        // Check if the move results in a win
        bool won = isWinningMove(row, col);
        if (won) { 
            displayBoard(board); // Display the board before declaring the winner
            cout << "Player " << currentPlayer << " wins!\n";
            return true; 
        }

        // Switch to the next player
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        return false; // No win; game continues
    }

    // Display the game board
    void display() const {
        displayBoard(board);
    }

    // Get the current player's symbol
    char getCurrentPlayer() const {
        return currentPlayer;
    }
};

int main() {
    PyramidTicTacToe game;
    int row, col;

    cout << "Welcome to Pyramid Tic-Tac-Toe!\n";
    game.display();

    while (true) {
        cout << "Player " << game.getCurrentPlayer() << ", enter your move (row and column): ";
        cin >> row >> col;

        if (game.playMove(row, col)) {
            break; // Exit the loop when a player wins
        }

        game.display();
    }

    cout << "Game over. Thank you for playing!\n";
    return 0;
}