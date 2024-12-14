#include "BoardGame_Classes.h"
#include "shared.h"
#include "Players.h"
#include <iostream>
#include "Boards.h"


class UserInterface {

private:
    Player<char>* players[2];
    Board<char>* Board;
    GameManager<char>* gameManger;
    int boardType;
    char Symbol[2] = {'X', 'O'};


    void take_players(){
        for (int i : {0, 1}) {
            int choice;
            cout << "Choose Player " << Symbol[i] << " type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch (this->boardType) {

                case 4:
                    if(choice == 1){
                        cout << "Enter your name: ";
                        string name;
                        cin >> name;
                        players[i] = new wordsXOPlayers<char>(name, Symbol[i], 3);
                    }
                    else if(choice == 2){
                        players[i] = new wordsXORandomPlayers<char>(Symbol[i], 3);
                    }
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
        cout << "3. Pyramid TicTacToe\n";
        cout << "4. Word TicTacToe\n";
        try{
            cin >> boardType;

        }
        catch (exception &e){
            cout << "Invalid choice. Please try again.\n";
            return set_board();
        }

        switch(boardType) {
            case 1:
                Board = new TicTacToe5x5();
                break;
            case 2:
                Board = new TicTacToeInverse();
                break;
            case 3:
                Board = new PyramidTicTacToe();
                break;
            case 4:
                Board = new WordTicTacToe();
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
        set_board();
        take_players();
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
