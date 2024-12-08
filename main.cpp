#include <iostream>
#include "Boards.h"
#include "Players.h"



int main() {
    int choice;
    Player<char>* players[2];
    Board<char>* B = new TicTacToeInverse;
    string playerXName, player2Name;
    char Symbol[2] = {'X', 'O'};

    cout << "Welcome to FCAI X-O Game. :)\n";

    for (int i : {0, 1}) {
        cout << "Choose Player " << Symbol[i] << " type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter Player " << Symbol[i] << " name: ";
                cin >> player2Name;
                players[i] = new HumanPlayer<char>(player2Name, Symbol[i], 3);
                break;
            case 2:
                players[i] = new SquareXORandomPlayers<char>(Symbol[i], 3);
                break;
            default:
                cout << "Invalid choice for Player " << Symbol[i] << ". Exiting the game.\n";
                return 1;
        }
    }

    // Create the game manager and run the game
    GameManager<char> game(B, players);
    game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    while (true){
        cout << "Do you want to play again? (y/n): ";
        char playAgain;
        cin >> playAgain;
        if (playAgain == 'y'){
            main();
        }
        else {
            cout << "Thank you for playing. Goodbye!\n";
            break;
        }
    }

    return 0;
}
