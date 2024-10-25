#include <iostream>
#include "Board.h"
#include <windows.h>
#include <cstdlib> 
#include <string>
using namespace std;

//Version 2
int main() {

	//Positions of the board
	string line, col;
	int iLine = -1, iCol = -1;
	// 0-computer, 1-user, 2-draw
	int winner = 2;
	//0-easy, 1-medium, 2-dificulty
	int dificulty;
	//Menu status
	bool menu = true;
	//Create a board
	Board board;
	//Input
	int input;
	bool inputValid = false;

	do {
		//Display the board
		board.printBoard();
		//Select dificulty
		cout << "\nSelect Dificulty:\n"
			<< "   1. Easy\n"
			<< "   2. Medium\n"
			<< "   3. Hard\n"
			<< "Make a selection(1/2/3): ";
		cin >> input;
		if (input == 1 || input == 2 || input == 3) {
			inputValid = true;
		}
		else {
			system("cls");
			cout << "Invalid Input please try again!\n\n";
		}
	} while (inputValid == false);
	board.setDificulty(input);

	system("cls");
	//If the player is first on not
	// true if the player is first, otherwise false
	bool playerFirst;
	inputValid = false;
	do {
		//Display board
		board.printBoard();

		cout << "Who goes first(Enter 1 for PC, Enter 2 for you): ";
		cin >> input;
		//Check if the input is valid
		if (!(input == 1 || input ==2)) {
			system("cls");
			cout << "Invalid input, please try again!\n";
		}
		else if (input == 1) { 
			playerFirst = false; 
			inputValid = true; 
		}
		else if (input == 2) {
			playerFirst = true; 
			inputValid = true;
		}

	} while (inputValid == false);
	

	system("cls");
	do {
		// Print the current state of the board
		board.printBoard();

		// Player's turn
		if (playerFirst) {
			cout << "Enter row position(A1,A2,A3): ";
			cin >> line;
			cout << "Enter column position(B1,B2,B3): ";
			cin >> col;

			//Check if the input if valid or not
			if (!(line == "A1" || line == "A2" || line == "A3") && !(col == "B1" || col == "B2" || col == "B3")) {
				system("cls");
				cout << "Invalid input, please try again.\n\n";
				continue;
			}

			// Translate input to index for the arrays
			if (line == "A1") iLine = 0;
			else if (line == "A2") iLine = 1;
			else if (line == "A3") iLine = 2;

			if (col == "B1") iCol = 0;
			else if (col == "B2") iCol = 1;
			else if (col == "B3") iCol = 2;

			// Check if the chosen position is valid
			if (board.checkPosition(iLine, iCol)) {
				board.setPosition(iLine, iCol, 1); // Player is 1 ('O')

				// Check for win
				if (board.checkWins()) {
					winner = board.getWinner();
					menu = false;
					break;
				}

				// Check for draw
				if (board.getBoardStatus()) {
					winner = 2; // Draw
					menu = false;
					break;
				}

				playerFirst = false; // Switch to computer's turn
			}
			else {
				cout << "Invalid move! Try again.\n\n";
			}

		}
		else {
			// Computer's turn based on the selected difficulty
			switch (board.getDificulty()) {
			case 1:
				board.computerPlay(); // Easy
				break;
			case 2:
				board.computerPlayMedium(); // Medium
				break;
			case 3:
				board.computerPlayMedium(); // Hard
				break;
			default:
				break;
			}

			// Check for win after the computer's move
			if (board.checkWins()) {
				winner = board.getWinner();
				menu = false;
				break;
			}

			// Check for draw
			if (board.getBoardStatus()) {
				winner = 2; // Draw
				menu = false;
				break;
			}

			playerFirst = true; // Switch back to player's turn
		}

		// Clear the screen and continue the loop
		system("cls");

	} while (menu == true);

	system("cls");
	board.printBoard();
	switch (winner)
	{
	case 0:
		system("color 0c"); //Red
		cout << "You lost. <GAME OVER>\n";
		break;
	case 1:
		system("color a"); //Green 
		cout << "Congratulations you won.\n";
		break;
	case 2:
		system("color E"); //Yellow
		cout << "The game is a draw.\n";
		break;
	default:
		system("color 7"); //White
		cout << "Error in identifying the winner.\n";
		break;
	}

	return 0;
}
