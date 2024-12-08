#ifndef BOARDGAMES_PLAYERS_H
#define BOARDGAMES_PLAYERS_H

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
        cout << "Enter your move from 0 to " << dimension - 1 << " (x y): ";
        cin >> x >> y;
    }
};


template <typename T>
class SquareXORandomPlayers: public RandomPlayer<T>{
public:

    SquareXORandomPlayers (T symbol, int dimension): RandomPlayer<T>(symbol){
        this->dimension = dimension;
        this->name = "Random Computer Player";
        srand(static_cast<unsigned int>(time(0)));
    };

    void getmove(int &x, int &y){
        x = rand() % this->dimension;  // Random number between 0 and dimension - 1
        y = rand() % this->dimension;  // Random number between 0 and dimension - 1
    }
};

#endif //BOARDGAMES_PLAYERS_H
