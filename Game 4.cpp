#include <iostream>
#include <vector>
#include <unordered_set>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

// Template function to display the 3x3 grid in a readable format
template <typename T>
void displayBoard(const vector<vector<T>> &board) {
    for (const auto &row : board) {
        for (const auto &cell : row) {
            // If cell is empty, display a dot, else show the letter
            cout << (cell == '\0' ? '.' : cell) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

class WordTicTacToe {
private:
    vector<vector<char>> board; // 3x3 game board
    unordered_set<string> dictionary; // Set to store valid words

    // Check if the given word exists in the dictionary
    bool isWordValid(const string &word) {
        return dictionary.find(word) != dictionary.end();
    }

    // Recursive function to form words in a specified direction
    bool formWord(int row, int col, int dx, int dy, string &currentWord) {
        // If out of bounds or the cell is empty, stop
        if (row < 0 || col < 0 || row >= 3 || col >= 3 || board[row][col] == '\0') {
            return false;
        }
        
        // Append the current letter to the word
        currentWord += board[row][col];

        // If the word is valid, return true
        return isWordValid(currentWord);
    }

public:
    WordTicTacToe() : board(3, vector<char>(3, '\0')) {}

    // Load words from a dictionary file into the set
    void loadDictionary(const string &filename) {
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
    bool makeMove(int row, int col, char letter) {
        if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != '\0') {
            cout << "Invalid move. Try again!" << endl;
            return false;
        }
        
        // Place the letter on the board
        board[row][col] = letter;
        return checkForWin(row, col);
    }

    // Check if the current move forms a valid word in any direction
    bool checkForWin(int row, int col) {
        string word = "";
        
        // Check horizontally
        if (formWord(row, 0, 0, 1, word)) return true;
        word.clear();

        // Check vertically
        if (formWord(0, col, 1, 0, word)) return true;
        word.clear();

        // Check diagonally (top-left to bottom-right)
        if (row == col && formWord(0, 0, 1, 1, word)) return true;
        word.clear();

        // Check diagonally (top-right to bottom-left)
        if (row + col == 2 && formWord(0, 2, 1, -1, word)) return true;

        return false;
    }

    // Display the current state of the game board
    void display() const {
        displayBoard(board);
    }

    // Check if the game has ended in a draw (no valid moves left)
    bool isGameDraw() const {
        for (const auto &row : board) {
            if (find(row.begin(), row.end(), '\0') != row.end()) {
                return false; // There's still space to play
            }
        }
        return true; // No moves left, game is a draw
    }
};

int main() {
    WordTicTacToe game;
    game.loadDictionary("dic.txt"); // Load words from dictionary file

    int row, col;
    char letter;
    bool gameOver = false;

    cout << "Welcome to Word Tic-Tac-Toe!" << endl;
    game.display(); // Show the empty board

    // Main game loop: alternating turns between players
    for (int turn = 1; turn <= 9; ++turn) {
        cout << "Player " << ((turn % 2 == 1) ? 1 : 2) << "'s turn (Enter row, col, letter): ";
        cin >> row >> col >> letter;

        if (game.makeMove(row, col, letter)) {
            cout << "Player " << ((turn % 2 == 1) ? 1 : 2) << " wins!" << endl;
            gameOver = true;
            break;
        }

        game.display(); // Show the updated board
    }

    // If no winner after 9 turns, check if the game ended in a draw
    if (!gameOver && game.isGameDraw()) {
        cout << "It's a draw!" << endl;
    }

    return 0;
}