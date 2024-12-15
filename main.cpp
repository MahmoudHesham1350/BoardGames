#include "BoardGame_Classes.h"
#include "shared.h"
#include "Players.h"
#include <iostream>
#include <limits>
#include "Boards.h"


class UserInterface {

private:
    Player<char>* players[2];
    Board<char>* Board;
    int board_max_size = 0;
    GameManager<char>* gameManger;
    int boardType = 0;
    char Symbol[2] = {'X', 'O'};


    void take_players(){
        for (int i : {0, 1}) {
            int choice;
            cout << "Choose Player " << Symbol[i] << " type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

                if(choice == 1){
                    cout << "Enter your name: ";
                    string name;
                    cin >> name;
                    switch (boardType) {
                        case 4:
                        {
                            players[i] = new wordsXOPlayers<char>(name, Symbol[i], board_max_size);
                            break;
                        }
                        case 5:
                        {
                            players[i] = new NumbersXOPlayers<char>(name, Symbol[i], board_max_size);
                            break;
                        }
                        default:
                        {
                            players[i] = new HumanPlayer<char>(name, Symbol[i], board_max_size);
                            break;
                        }

                    }
                }
                else if(choice == 2){
                    switch (boardType) {
                        case 4:
                        {
                            players[i] = new wordsXORandomPlayers<char>(Symbol[i], board_max_size);
                            break;
                        }
                        case 5:
                        {
                            players[i] = new NumbersXORandomPlayers<char>(Symbol[i], board_max_size);
                            break;
                        }
                        default:
                        {
                            players[i] = new SquareXORandomPlayers<char>(Symbol[i], board_max_size);
                            break;
                        }
                    }
                }
                else {
                    cout << "Invalid choice." << endl;
                    return take_players();
                }





        }
    }

    void set_board(){
        int choice;
        cout << "Choose the game type:\n";
        cout << "1. TicTacToe 5x5\n";
        cout << "2. TicTacToe Inverse\n";
        cout << "3. Pyramid TicTacToe\n";
        cout << "4. Word TicTacToe\n";
        cout << "5. NumbersOX\n";
        cout << "8. Sus TicTacToe\n";
        cout << "9. Ultimate TicTacToe\n";

        cin >> boardType;

        if (cin.fail()) {
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cerr << "Invalid choice." << endl;
            return set_board();
        }

        switch(boardType) {
            case 1:
            {
                Board = new TicTacToe5x5();
                board_max_size = 5;
                break;
            }
            case 2:
            {
                Board = new TicTacToeInverse();
                board_max_size = 3;
                break;
            }
            case 3:
            {
                Board = new PyramidTicTacToe();
                board_max_size = 5;
                break;
            }
            case 4:
            {
                Board = new WordTicTacToe();
                board_max_size = 3;
                break;
            }
            case 5:
            {
                Board = new NumbersOX();
                board_max_size = 3;
                break;
            }
            case 8:
            {
                Board = new SusTicTacToe();
                board_max_size = 3;
                Symbol[0] = 'S';
                Symbol[1] = 'U';
                break;
            }
            case 9: {
                Board = new UltimateTicTacToe();
                board_max_size = 3;
                break;
            }
            default:
            {
                cout << "Invalid choice." << endl;
                return set_board();
            }
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
        cout << "Do you want to play again? (y/n):";
        cin.clear();
        cout.flush();
        char playAgain;
        cin >> playAgain;
        if (playAgain == 'y'){
            UserInterface();
        }
        else if(playAgain == 'n'){
            cout << "\nThank you for playing. Goodbye!\n";
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
