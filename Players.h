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
    wordsXOPlayers (string name, T symbol, int dimension): HumanPlayer<T>(name, symbol, dimension) {

    }

    void getmove(int &x, int &y) override{
        HumanPlayer<T>::getmove(x, y);
        char character;
        while(true){
            cout << "Enter a character: ";
            try {
                cin >> character;
                character = toupper(character);
                if (character >= 'A' && character <= 'Z'){
                    this->symbol = character;
                    break;
                }
                else {
                    throw exception();
                }
            }
            catch (exception &e){
                cout << "Invalid character. Please try again.\n";
            }

        }

    }
};




#endif //BOARDGAMES_PLAYERS_H
