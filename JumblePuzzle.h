/*
 * JumblePuzzle.h
 *
 * Header File for Assignment 4
 * By: Tyler Doyle
 *
 * This code will create a hidden word search (jumble puzzle) based off a given word and difficulty.
 */

#include <string>
#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;

typedef char* charArrayPtr; // Defined for easy of use (instead of char**)

class BadJumbleException { // Exception class for invalid inputs upon jumble puzzle creation
public:
	BadJumbleException(const string& message);
	string& what();
private:
	string message;
};

class JumblePuzzle {
public:
	JumblePuzzle(const string& word, const string& diff); // Simple constructor
	JumblePuzzle(const JumblePuzzle& right); // Copy constructor
	int getSize() const; // Accessor for the puzzle size
	charArrayPtr* getJumble() const; // Accessor for the puzzle itself
	int getRowPos() const; // Accessor for the starting row of the word
	int getColPos() const; // Accessor for the starting column of the word
	char getDirection() const; // Accessor for the direction the word is hidden in (n, e, s, w)
	JumblePuzzle& operator=(const JumblePuzzle& right); // Equality operator
	virtual ~JumblePuzzle(); // Destructor
private:
	charArrayPtr* newPuzzle() const; // Initializes an empty jumble puzzle
	charArrayPtr* fillPuzzle(charArrayPtr* puzzle) const; // Fill in the puzzle with random letters
	charArrayPtr* createJumble(const string& word); // Creates the jumble puzzle by hiding the word supplied
	char assignDirection() const; // Assigns the attribute based off a random int (0, 1, 2, 3)
	int generateRandomNum(const int& limit) const; // Generate a random number between 0 and (1 - limit)
	char generateLetter() const; // Generate a random letter (used to fill in the puzzle)
	// Attributes
	charArrayPtr* jumble; // Jumble puzzle
	int size; // Size of the puzzle (length * difficulty)
	int row; // Starting row of the hidden word
	int col; // Starting column of the hidden word
	char direction; // Direction of the hidden word
};
