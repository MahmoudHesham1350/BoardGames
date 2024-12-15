#ifndef BOARDGAMES_PLAYERS_H
#define BOARDGAMES_PLAYERS_H

#include <limits>
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
public:
    NumbersXOPlayers (std::string name, T symbol, int dimension): HumanPlayer<T>(name, symbol, dimension) {}

    void getmove(int &x, int &y) override{
        HumanPlayer<T>::getmove(x, y);
        int character;
        while(true){
            cout << "Enter a Number between (1 and 9): " << endl;
            cin >> character;


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





#endif //BOARDGAMES_PLAYERS_H
