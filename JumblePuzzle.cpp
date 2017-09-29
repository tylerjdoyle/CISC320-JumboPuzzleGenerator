/*
 * JumblePuzzle.cpp
 *
 *  Source code for Assignment 4
 *  By: Tyler Doyle (10129777)
 */

#include "JumblePuzzle.h"

using namespace std;

BadJumbleException::BadJumbleException(const string& message) : message(message) {}
string& BadJumbleException::what() { return message; }

JumblePuzzle::JumblePuzzle(const string& word, const string& diff) {
	if (word.length() < 3)
		throw BadJumbleException("That word is too short!");
	else if (word.length() > 10)
		throw BadJumbleException("That word is too long!");
	int length = word.length();
	for (int i = 0; i < length; i++)
		if (!((word[i] <= 'z' && word[i] >= 'a') || (word[i] <= 'Z' && word[i] >= 'A')))
			throw BadJumbleException("Please only input letters.");
	if (diff == "easy")
		size = length * 2;
	else if (diff == "medium")
		size = length * 3;
	else if (diff == "hard")
		size = length * 4;
	else
		throw BadJumbleException("Please select a valid difficulty.");
	srand(time(NULL)); // seeds random number generation
	jumble = createJumble(word);
}

JumblePuzzle::JumblePuzzle(const JumblePuzzle& right) {
	size = right.getSize();
	direction = right.getDirection();
	col = right.getColPos();
	row = right.getRowPos();
	jumble = newPuzzle();
	int j;
	for (int i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			jumble[i][j] = right.getJumble()[i][j];
}

charArrayPtr* JumblePuzzle::createJumble(const string& word) {
	charArrayPtr* puzzle = newPuzzle();
	fillPuzzle(puzzle);
	bool placed = false;
	int currentRow, currentCol, counter;
	string dir;
	while (!placed) {
		counter = 0;
		currentRow = generateRandomNum(size - 1);
		currentCol = generateRandomNum(size - 1);
		row = currentRow;
		col = currentCol;
		direction = assignDirection();
		while (!placed && currentRow < size && currentCol < size
				&& currentRow >= 0 && currentCol >= 0) {
			if (word[counter + 1] == '\0') {
				placed = true;
			}
			puzzle[currentRow][currentCol] = word[counter];
			if (direction == 'e') // right
				currentCol++;
			else if (direction == 's') // down
				currentRow++;
			else if (direction == 'w') // left
				currentCol--;
			else //up
				currentRow--;
			counter++;
		}
	}
	return puzzle;
}

char JumblePuzzle::assignDirection() const {
	int dir = generateRandomNum(4);
	if (dir == 0) // right
		return 'e';
	else if (dir == 1) // down
		return 's';
	else if (dir == 2) // left
		return 'w';
	else //up
		return 'n';
}

int JumblePuzzle::generateRandomNum(const int& limit) const { return rand() % limit; }

char JumblePuzzle::generateLetter() const {
	char temp = 97 + generateRandomNum(24); // 97 corresponds to 'a'
	return temp;
}

charArrayPtr* JumblePuzzle::fillPuzzle(charArrayPtr* puzzle) const {
	int j;
	for (int i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			puzzle[i][j] = generateLetter();
	return puzzle;
}

charArrayPtr* JumblePuzzle::newPuzzle() const {
	charArrayPtr* puzzle = new char*[size];
	for (int j = 0; j < size; j++)
			puzzle[j] = new char[size];
	return puzzle;
}

JumblePuzzle& JumblePuzzle::operator=(const JumblePuzzle& right) {
	if (this != &right) {
		int i;
		for (i = 0; i < size; i++) {
			delete[] jumble[i];
			jumble[i] = nullptr;
		}
		delete[] jumble;
		jumble = nullptr;
		*this = JumblePuzzle(right);
	}
	return *this;
}

charArrayPtr* JumblePuzzle::getJumble() const { return jumble; }
int JumblePuzzle::getSize() const { return size; }
int JumblePuzzle::getRowPos() const { return row; }
int JumblePuzzle::getColPos() const { return col; }
char JumblePuzzle::getDirection() const { return direction; }

JumblePuzzle::~JumblePuzzle() {
	for (int i = 0; i < size; i++) {
		delete[] jumble[i];
		jumble[i] = nullptr;
	}
	delete[] jumble;
	jumble = nullptr;
}
