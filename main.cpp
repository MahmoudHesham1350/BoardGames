#include <iostream>
#include "Boards.h"
#include "Players.h"

class UserInterface {

private:
    Player<char>* players[2];
    Board<char>* Board;
    GameManager<char>* gameManger;
    char Symbol[2] = {'X', 'O'};

    void take_players(){
        for (int i : {0, 1}) {
            int choice;
            cout << "Choose Player " << Symbol[i] << " type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            string playerName;
            switch(choice) {
                case 1:
                    cout << "Enter Player " << Symbol[i] << " name: ";
                    cin >> playerName;
                    players[i] = new HumanPlayer<char>(playerName, Symbol[i], 5);
                    break;
                case 2:
                    players[i] = new SquareXORandomPlayers<char>(Symbol[i], 5);
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    return take_players();
            }
        }
};

    void set_board(){
        int choice;
        cout << "Choose the game type:\n";
        cout << "1. TicTacToe 5x5\n";
        cout << "2. TicTacToe Inverse\n";
        cin >> choice;

        switch(choice) {
            case 1:
                Board = new TicTacToe5x5();
                break;
            case 2:
                Board = new TicTacToeInverse();
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                return set_board();
        }
    }

    void set_game_manager(){
        gameManger = new GameManager<char>(Board, players);
    }



public:
    UserInterface(){
        take_players();
        set_board();
        set_game_manager();
        this->gameManger->run();

        cout << "Do you want to play again? (y/n): ";
        char playAgain;
        cin >> playAgain;
        if (playAgain == 'y'){
            UserInterface();
        }
        else if(playAgain == 'n'){
            cout << "Thank you for playing. Goodbye!\n";
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    ~UserInterface(){
        delete Board;
        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }
        delete gameManger;
    }
};

int main() {
    UserInterface();


    return 0;
}
