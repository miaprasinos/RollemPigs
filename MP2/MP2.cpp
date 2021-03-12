// MP2
// 10-1-2020
// Mia Prasinos
// Runs a game of Roll'em Pigs between the user and the computer.
// It uses various functions and random number generators to roll dice and keep track of the score. 

#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>   
#include <cstdlib>
#include <ctime>
using namespace std;

// function prototypes
int rollDie(void);
int rollDice(void);
bool isTurnScoreLost(int die1value, int die2value);
bool isGameScoreLost(int die1value, int die2value);
char getUserInput(void);
char switchPlayer(char player);

// initializes variables to hold dice integers
int diceOne = 0;
int diceTwo = 0;
int diceSum = 0;

// initializes roll again
char rollAgain = 'a';

//initializes variable to determine current player, either 'p' for player or 'c' for computer
char currentPlayer = 'p';

// initializes variables to hold turn and game totals
int turnTotal = 0;
int playerTotal = 0;
int computerTotal = 0;

int main() {

	// starts the game
	cout << "Oink oink let's play Roll'em pigs! Try to beat the computer!" << endl;
	cout << endl;

	srand(time(0));

	// checks to make sure both total scores are less than 100 before starting turns
	while (playerTotal < 100 && computerTotal < 100) {
		// turn for user
		if (currentPlayer == 'p') {
			getUserInput();
			rollDice();
			isTurnScoreLost(diceOne, diceTwo);
			isGameScoreLost(diceOne, diceTwo);
		}
		// turn for computer
		if (currentPlayer == 'c') {
			rollDice();
			isTurnScoreLost(diceOne, diceTwo);
			isGameScoreLost(diceOne, diceTwo);
			// checks if turnTotal is greater than 25 to end computer's turn
			if (turnTotal >= 25) {
				computerTotal = computerTotal + turnTotal;
				switchPlayer(currentPlayer);
			}
		}
	}
	// determines which player reached 100 or greater and gives the winning title at the end
	if (playerTotal >= 100) {
		cout << "Player wins!!!";
		return 0;
	}
	else if (computerTotal >= 100) {
		cout << "Computer wins!!!";
		return 0;
	}
}

/**
	Generates a random number to stimulate rolling a die.
	@return dice roll the integer from the roll. 
*/
int  rollDie(void) {
	int diceRoll = (rand() % 6) + 1;
	return diceRoll;
	
}

/**
	Rolls both dice and determines the sum of the numbers, displays both dice values.
	@return diceSum the sum of the dice rolled.
*/
int rollDice(void) {

	rollDie(); // rolls the dice to get first value
	diceOne = rollDie(); // stores value in variable
	rollDie(); // rolls the dice to get second variable
	diceTwo = rollDie(); // stores value in second variable

	diceSum = diceOne + diceTwo; // adds together to make getting the turnTotal easier

	cout << "Die one: " << diceOne << " Die two: " << diceTwo << endl; // display's die values so players can see what they got

	return diceSum;
}

/**
	Sees if an individual die has a one and resets the turn score if so.
	@param die1value amount from die one roll
	@param die2value amount from die two roll
	@return true if there is a one, false if there is not.
*/
bool isTurnScoreLost(int die1value, int die2value) {
	if (die1value == 1 || die2value == 1) {
		cout << "Turn lost" << endl;
		switchPlayer(currentPlayer);
		
		return true;
	}
	else {
		turnTotal = turnTotal + diceSum;
		cout << "Turn Total is: " << turnTotal << endl;
		return false;
	}
}

/**
	Sees if both dice have a one and resets the game score if so.
	@param die1value amount from die one roll
	@param die2value amount from die two roll
	@return true if both die are one, false if not.
*/
bool isGameScoreLost(int die1value, int die2value) {
	if (die1value == 1 && die2value == 1) {
		if (currentPlayer == 'p') {
			playerTotal = 0;
			cout << "Turn lost" << endl;
			switchPlayer(currentPlayer);
		}
		else if (currentPlayer == 'c') {
			computerTotal = 0;
			switchPlayer(currentPlayer);
		}
		
		return true;
	}
	else {
		
		return false;
	}
}

/**
	Prompt user if they want to roll the dice again, prompt for correct input if entered incorrectly
	@return r if the user wants to roll, s if they do not, and lets the user know if incorrect input to try again.
*/
char getUserInput(void) {
	cout << "Would you like to roll (r) or stop your turn (s): ";
	cin >> rollAgain;

	if (rollAgain == 'r') {
		cout << "Rolling again" << endl;
		cout << endl;
		return 'r';
	}
	else if (rollAgain == 's') {
		playerTotal = playerTotal + turnTotal;
		switchPlayer(currentPlayer);
		return 's';
	}
	else {
		cout << "Incorrect input. Please enter another option: " << endl;
		getUserInput();
	}

}

/**
	Switches the user at the end of a turn, resets turnTotal and dice values, and displays total scores during user changes
	@param player uses whichever player's turn it is now
	@return currentPlayer
*/
char switchPlayer(char player) {
	turnTotal = 0;
	diceOne = 0;
	diceTwo = 0;
	if (currentPlayer == 'p') {
		currentPlayer = 'c';
		rollAgain = 's';
		cout << "Player Total is: " << playerTotal << endl;
		char randomChar = ' ';
		cout << "enter anything to start computers turn: "; // makes program wait go to computer turn to avoid bugs
		cin >> randomChar;
		cout << endl;
	}
	else if (currentPlayer == 'c') {
		currentPlayer = 'p';
		rollAgain = 's';
		cout << "Computer Total is: " << computerTotal << endl;
		cout << "Player's Turn" << endl;
		cout << endl;
	}
	return currentPlayer;
}


