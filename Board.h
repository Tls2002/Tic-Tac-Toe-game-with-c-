#include <iostream>
#include <ctime>
using namespace std;

 //Version 2
class Board{
private:
	//If player is 0, it indicates the computer wins
	//If player is 1, it indicates the player wins
	int winner = 2;

	//Positions of the board
	char positions[3][3] = { {' ',' ',' '},{' ',' ',' '},{' ',' ', ' '} };
	
	bool computerPlayed;
	// 0 - select, 1- easy, 2- medium, 3- hard
	int dificulty = 0;

public:
	
	// 0 - for invalid
	//
	/*/Errors classes
	class Error {
	public:
		int numError;
		Error(int num) {
			numError = num;
		}
	};*/

	//Constructors
	Board() {
		computerPlayed = false;
	}
	~Board() {
		
	}

	//Functions to check if the board if full or not
	//Return false if the board is not full
	//Return true if the board is full
	bool getBoardStatus() {
		for (int l = 0; l < 3;l++) {
			for(int c = 0;c<3;c++)
			if (positions[l][c] == ' ')
				return false;
		}
		return true;
	}

	//Check if position is empty
	//If the position is empty return true, otherwise return false
	bool checkPosition(int L,int C) {
		if (positions[L][C] == ' ') {
			return true;
		}
		return false;
		
	};

	//Automate computer play easy mode *
	void computerPlay() {
		srand(time(0));
		int randomL;
		int randomC;
		do{
			randomL = rand() % 3;
			randomC = rand() % 3;
		}while (checkPosition(randomL, randomC) == false);
		setPosition(randomL, randomC, 0);
	}

	//Automate computer play hard mode *
	void computerPlayMedium() {
		
		//Check if computer can win the next move
		for (int l = 0; l < 3; l++) {
			for (int c = 0; c < 3; c++) {
				if (positions[l][c] == ' ') {
					positions[l][c] = 'X';
					if (checkWins() && winner == 0) {
						computerPlayed = true;
						return;
					}
					positions[l][c] = ' ';
				}
			}
		}

		//Block player from winning
		for (int l = 0; l < 3; l++) {
			for (int c = 0; c < 3; c++) {
				if (positions[l][c] == ' ') {
					positions[l][c] = 'O';
					if (checkWins() && winner == 1) {
						positions[l][c] = 'X';
						computerPlayed = true;
						return;
					}
					positions[l][c] = ' ';
				}
			}
		}

		//Take the center
		if (positions[1][1] == ' ') {
			setPosition(1, 1, 0);
			computerPlayed = true;
			return;
		}

		//Take corners if empty
		int corners[4][2] = { {0,0},{0,2},{2,0},{2,2} };
		for (int i = 0; i < 4; i++) {
			int l = corners[i][0];
			int c = corners[i][1];
			if (positions[l][c] == ' ') {
				setPosition(l, c, 0);
				computerPlayed = true;
				return;
			}
		}

		//Take any available spot
		computerPlay();

	}


	//Function to get the winner *
	int getWinner() const{
		return winner;
	}

	//Check Wins *
	bool checkWins() {
		
		//Lines matched
		if (positions[0][0] == positions[0][1] && positions[0][1] == positions[0][2] && positions[0][0] != ' ') {
			if (positions[0][0] == 'X') {
				winner = 0;
			}
			else if (positions[0][0] == 'O') {
				winner = 1;
			}
			return true;
		}
		if (positions[1][0] == positions[1][1] && positions[1][1] == positions[1][2] && positions[1][0] != ' ') {
			if (positions[1][0] == 'X') {
				winner = 0;
			}
			else if (positions[1][0] == 'O') {
				winner = 1;
			}
			return true;
		}
		if (positions[2][0] == positions[2][1] && positions[2][1] == positions[2][2] && positions[2][0] != ' ') {
			if (positions[2][0] == 'X') {
				winner = 0;
			}
			else if (positions[2][0] == 'O') {
				winner = 1;
			}
			return true;
		}

		//Columns matched
		if (positions[0][0] == positions[1][0] && positions[1][0] == positions[2][0] && positions[0][0] != ' ') {
			if (positions[0][0] == 'X') {
				winner = 0;
			}
			else if (positions[0][0] == 'O') {
				winner = 1;
			}
			return true;
		}
		if (positions[0][1] == positions[1][1] && positions[1][1] == positions[2][1] && positions[0][1] != ' ') {
			if (positions[0][1] == 'X') {
				winner = 0;
			}
			else if (positions[0][1] == 'O') {
				winner = 1;
			}
			return true;
		}
		if (positions[0][2] == positions[1][2] && positions[1][2] == positions[2][2] && positions[0][2] != ' ') {
			if (positions[0][2] == 'X') {
				winner = 0;
			}
			else if (positions[0][2] == 'O') {
				winner = 1;
			}
			return true;
		}

		//Crosses
		if (positions[0][0] == positions[1][1] && positions[1][1] == positions[2][2] && positions[0][0] != ' ') {
			if (positions[0][0] == 'X') {
				winner = 0;
			}
			else if (positions[0][0] == 'O') {
				winner = 1;
			}
			return true;
		}
		if (positions[0][2] == positions[1][1] && positions[1][1] == positions[2][0] && positions[0][2] != ' ') {
			if (positions[0][2] == 'X') {
				winner = 0;
			}
			else if (positions[0][2] == 'O') {
				winner = 1;
			}
			return true;
		}
		return false;
	}

	//Function to fill a position *
	//if the player = 0 the computer is playing
	//if the player = 1 the user is playing
	void setPosition(int line,int col,int player) {

		if (player == 0) {
			positions[line][col] = 'X';
		}
		else if (player == 1) {
			positions[line][col] = 'O';
		}
	};

	//Function to print the board game *
	void printBoard() const{
		cout << "	Tic-Tac-Toe Game\n\n"
			<< "       B1      B2      B3   \n"
			<< "   _________________________\n"
			<< "   |       |       |       |\n"
			<< "A1 |   " << positions[0][0] << "   |   " << positions[0][1] << "   |   " << positions[0][2] << "   |" << "	PC:X\n"
			<< "   |       |       |       |" << "	You:O\n"	
			<< "   _________________________" << "	Dificulty: " << getDificultyName() << endl
			<< "   |       |       |       |\n"
			<< "A2 |   " << positions[1][0] << "   |   " << positions[1][1] << "   |   " << positions[1][2] << "   |\n"
			<< "   |       |       |       |\n"
			<< "   _________________________\n"
			<< "   |       |       |       |\n"
			<< "A3 |   " << positions[2][0] << "   |   " << positions[2][1] << "   |   " << positions[2][2] << "   |\n"
			<< "   |       |       |       |\n"
			<< "   -------------------------\n";
	}

	//Set the dificulty
	void setDificulty(int d) {
		dificulty = d;
	}

	//Get the dificulty name
	string getDificultyName() const {
		// 0 - select, 1- easy, 2- medium, 3- hard
		switch (dificulty)
		{
		case 0:
			return "Select";
			break;
		case 1:
			return "Easy";
			break;
		case 2:
			return "Medium";
			break;
		case 3:
			return "Hard";
			break;
		default:
			return "Error";
			break;
		}
	}

	//get dificulty
	int getDificulty() const{
		return dificulty;
	}
};
