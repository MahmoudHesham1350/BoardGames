#ifndef BOARDGAMES_PLAYERS_H
#define BOARDGAMES_PLAYERS_H

#include <limits>
#include <algorithm>
#include "BoardGame_Classes.h"


template <typename T>
class HumanPlayer : public Player<T> {
private:
    int dimension;
public:
    HumanPlayer(std::string name, T symbol, int dimension) : Player<T>(name, symbol) {
        this->dimension = dimension;
    };

    void getmove(int &x, int &y) {
        cout << "Enter your move 2D zero indexed" << endl;
        cin >> x >> y;
    }
};


template <typename T>
class SquareXORandomPlayers: public RandomPlayer<T>{
public:

    SquareXORandomPlayers (T symbol, int dimension): RandomPlayer<T>(symbol){
        this->dimension = dimension;
        this->name = "Random Computer Player " + std::string(1, symbol);
        srand(static_cast<unsigned int>(time(0)));
    };

    void getmove(int &x, int &y){
        x = rand() % this->dimension;  // Random number between 0 and dimension - 1
        y = rand() % this->dimension;  // Random number between 0 and dimension - 1
    }
};


template <typename T>
class wordsXORandomPlayers: public SquareXORandomPlayers<T>{
public:
    wordsXORandomPlayers (T symbol, int dimension): SquareXORandomPlayers<T>(symbol, dimension) {};

    void getmove(int &x, int &y) override{
        SquareXORandomPlayers<T>::getmove(x, y);
        this->symbol = 'A' + rand() % 26;
    }
};


template <typename T>
class wordsXOPlayers: public HumanPlayer<T>{
public:
    wordsXOPlayers (std::string name, T symbol, int dimension): HumanPlayer<T>(name, symbol, dimension) {}

    void getmove(int &x, int &y) override{
        HumanPlayer<T>::getmove(x, y);
        char character;
        while(true){
            cout << "Enter a character: " << endl;
            cin >> character;
            character = toupper(character);

            if (cin.fail() || character < 'A' || character > 'Z'){
                cin.clear(); // clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid character." << endl;
            }
            else {
                this->symbol = character;
                break;
            }
        }
    }
};


template <typename T>
class NumbersXOPlayers: public HumanPlayer<T>{
private:
    vector<char> numbers;
public:
    NumbersXOPlayers (std::string name, T symbol, int dimension): HumanPlayer<T>(name, symbol, dimension) {
        if (symbol == 'X'){
            numbers = {'1', '3', '5', '7', '9'};
        }
        else {
            numbers = {'2', '4', '6', '8'};
        }
    }

    void getmove(int &x, int &y) override {
        HumanPlayer<T>::getmove(x, y);
        char number;
        while(true){
            cout << "Enter a Number from {";
            for (int i = 0; i < numbers.size(); ++i) {
                cout << numbers[i] << (i == numbers.size() - 1 ? "" : ", ");
            }
            cout << "}" << endl;
            cin >> number;


            if (cin.fail() ){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid character." << endl;
                continue;
            }

            if (find(numbers.begin(), numbers.end(), number) == numbers.end()){
                cout << "Invalid number." << endl;
            }
            else {
                this->symbol = number;
                numbers.erase(std::remove(numbers.begin(), numbers.end(), number), numbers.end());
                break;
            }

        }
    }
};

template <typename T>
class NumbersXORandomPlayers: public SquareXORandomPlayers<T>{
private:
    vector<char> numbers;
public:
    NumbersXORandomPlayers(T symbol, int dimension): SquareXORandomPlayers<T>(symbol, dimension) {
        if (symbol == 'X'){
            numbers = {'1', '3', '5', '7', '9'};
        }
        else {
            numbers = {'2', '4', '6', '8'};
        }
    };

    void getmove(int &x, int &y) override{
        SquareXORandomPlayers<T>::getmove(x, y);
        this->symbol = numbers[rand() % numbers.size()];
    }
};

// Human player class
class FourInARowPlayer : public Player<char> {
public:
    FourInARowPlayer(string n, char symbol) : Player<char>(n, symbol) {}

    void getmove(int& x, int& y) override {
        cout << name << " (" << symbol << "), enter column (0-6): ";
        cin >> y;
        x = 0; // X is not relevant for column-based updates
    }
};

// Human player class
class FourInARowRandomPlayer : public RandomPlayer<char> {
public:
    FourInARowRandomPlayer(char symbol, int dimension) : RandomPlayer<char>(symbol) {}

    void getmove(int& x, int& y) override {
        x = 0; // X is not relevant for column-based updates
        y = rand() % dimension;
    }
};



#endif //BOARDGAMES_PLAYERS_H
