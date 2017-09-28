/*
	Andrew Maclean
	May 24, 2017
	Boggle Game
*/

#ifndef WORDTREE_H
#define WORDTREE_H

#include <queue>
#include <string>
#include <time.h>
#include <iomanip>

const int ALPHALENGTH = 26;
const int BOGGLEDIM = 4;

using namespace std;

class Alphabet;

// nodes of letters and their pointers to new alphabets
class Letter {
public:
	Letter() : found(false), next(NULL) {}
	Alphabet* getNext() { return next; }
	void setNext(Alphabet* newNext) { next = newNext; }
	bool isFound() { return found; }
	void setFound() { found = true; }
	~Letter() {}
private:
	bool found;
	Alphabet* next;
};

// a 24 element array of letters
class Alphabet {
public:
	Alphabet() {
		for (int i = 0; i < ALPHALENGTH; i++) {
			Letter* ltr = new Letter();
			Charset[i] = ltr;
		}
	}
	Letter** getAlpha() { return Charset; }
	~Alphabet() {}
private:
	Letter* Charset[ALPHALENGTH];
};

// a dictionary of all elements loaded in
class BoggleDict {
public:

	// default constructor
	BoggleDict() {
		ptrToFirst = NULL;
	}

	// makes a queue from the string passed
	queue<char> queueWord(const string& newWord) {
		queue<char> word;
		int size = newWord.size();
		for (int i = 0; i < size; i++)
			word.push(newWord[i]);

		return word;
	}

	// adds a word to the tree
	bool addWord(const string& newWord) {

		if (newWord == "")
			return false;
		else {
			queue<char> word = queueWord(newWord);
			if (ptrToFirst == NULL)
				ptrToFirst = new Alphabet();

			Alphabet* alpha = ptrToFirst;
			while (word.size() > 0) {
				Letter** alphArr = alpha->getAlpha();

				int loc = int(word.front()) - 97;
				if (!alphArr[loc]->isFound()) {
					alphArr[loc]->setFound();
				}
				else if (alphArr[loc]->isFound() && word.size() == 1)
					return false;

				if (alphArr[loc]->getNext() == NULL && word.size() > 1)
					alphArr[loc]->setNext(new Alphabet());

				alpha = alphArr[loc]->getNext();

				word.pop();
			}
		}
		return true;
	}

	// prints all the words in the tree
	void print() {
		printRec(ptrToFirst, "");
	}
	
	// determines if a string is valid
	bool isPrefix(string newWord) {
		if (ptrToFirst == NULL)
			return false;
		else {
			queue<char> word = queueWord(newWord);
			Alphabet* alpha = ptrToFirst;
			while (word.size() > 0) {
				int loc = char(word.front() - 97);
				if (alpha == NULL)
					return false;
				else if (alpha->getAlpha()[loc]->isFound()) {
					word.pop();
					alpha = alpha->getAlpha()[loc]->getNext();
				}
				else
					return false;
			}
		}
		return true;
	}

	// determines if a string ends in null
	bool isWord(string newWord) {
		if (ptrToFirst == NULL)
			return false;
		else {
			queue<char> word = queueWord(newWord);
			Alphabet* alpha = ptrToFirst;
			while (word.size() > 0) {
				int loc = char(word.front() - 97);
				if (alpha == NULL)
					return false;
				else if (alpha->getAlpha()[loc]->isFound()) {
					word.pop();
					alpha = alpha->getAlpha()[loc]->getNext();
				}
				else
					return false;
			}
			return (alpha == NULL);
		}
	}

	// deletes all the alphabets
	void del(Alphabet* alpha) {
		for (int i = 0; i < ALPHALENGTH; i++) {
			if (alpha->getAlpha()[i]->getNext() != NULL) {
				alpha = alpha->getAlpha()[i]->getNext();
				del(alpha);
			}
		}
		delete alpha;
	}

	// reads a file and gets all the words
	void read(const string& fileName) {
		ifstream input(fileName);
		int i = 0;
		string line;
		bool added;
		if (input.is_open()) {
			while (getline(input, line)) {
				added = addWord(line);
				if (added)
					i++;
			}
			input.close();
			cout << i << " words loaded" << endl;
		}
		else { cout << "file not found" << endl; }
	}

	// destructor
	~BoggleDict() {
		del(ptrToFirst);
	}

private:

	// recursive printing function
	void printRec(Alphabet* alpha, string prefix) {
		if (alpha == NULL) {
			cout << endl;
		}
		else {
			bool preTest = false;
			for (int i = 0; i < ALPHALENGTH; i++) {
				if (alpha->getAlpha()[i]->isFound()) {

					if (preTest) {
						prefix = prefix.substr(0, prefix.size() - 1);
						out(prefix + char(i + 97));
					}
					else
						out("" + char(i + 97));
					preTest = true;
					prefix += char(i + 97);
					printRec(alpha->getAlpha()[i]->getNext(), prefix);
				}
			}
		}
	}

	// specifies whatever output method
	void out(const string& input) const {
		cout << input << endl;
	}

	Alphabet* ptrToFirst;

};

// a field on the Boggle board
class BoggleField {
public:
	BoggleField() : checked(false), letter(' ') {}
	bool isChecked() {return checked;}
	void setChecked() {checked = true;}
	void unCheck() { checked = false; }
	char getLetter() { return letter; }
	void setLetter(char newLetter) { letter = newLetter; }
	~BoggleField() {}
private:
	char letter;
	bool checked;
};

// a structure of words and how often they are found
struct word {
	string foundWord;
	int wordCount;
};

// actual game class
class BoggleGame {
public:
	// default constructor
	BoggleGame() {
		string fileName;
		cout << "Enter the name of your dictionary file minus the \".txt\" " << endl;
		cin >> fileName;
		cout << "loading dictionary..." << endl;
		bog = new BoggleDict();
		bog->read(fileName + ".txt");
		foundWordsCount = 0;
		showBoard = "";
		for (int i = 0; i < BOGGLEDIM; i++) {
			for (int j = 0; j < BOGGLEDIM; j++)
				board[j][i] = new BoggleField();
		}
	}

	// makes a random Boggle board
	void makeRandomBoard() {
		srand(time(NULL));
		char a;
		for (int i = 0; i < BOGGLEDIM; i++) {
			for (int j = 0; j < BOGGLEDIM; j++) {
				a = char(rand() % 26 + 97);
				board[j][i]->setLetter(a);
			}
		}

		printBoard();
	}

	// makes a user defined Boggle board
	void makeBoard() {
		char a;
		cout << "Enter 16 letters seperated by spaces or returns" << endl;
		for (int i = 0; i < BOGGLEDIM; i++) {
			for (int j = 0; j < BOGGLEDIM; j++) {
				cin >> a;
				board[j][i]->setLetter(a);
			}
		}
	}

	// finds all the words on the board
	void findWords() {
		string prefix = "";
		string a;
		cout << "would you like to see the soutions (y/n)?" << endl;
		cin >> a;
		showBoard = a;

		for (int i = 0; i < BOGGLEDIM; i++) {
			for (int j = 0; j < BOGGLEDIM; j++) {
				if (checkWord(i, j, prefix)) {
					prefix += board[j][i]->getLetter();
					checkAdjacent(i, j, prefix);
					board[j][i]->unCheck();
					prefix = "";
				}
			}
		}

		cout << endl;
		for (int i = 0; i < foundWordsCount; i++)
			cout << setw(10) << foundWords[i].foundWord << ", count: " << foundWords[i].wordCount << endl;
	}

	// prints the board in its current state
	void printBoard() {
		for (int i = 0; i < BOGGLEDIM; i++) {
			for (int j = 0; j < BOGGLEDIM; j++)
				if (board[j][i]->isChecked())
					cout << '\'' << board[j][i]->getLetter() << '\'' << ' ';
				else
					cout << setw(3) << board[j][i]->getLetter() << ' ';
			cout << endl;
		}
	}

	// destructor
	~BoggleGame() {

	}

private:
	// determines if the position of a letter is usable
	bool letterBounds(int i, int j) {
		if (i < 0 || i >= BOGGLEDIM ||
			j < 0 || j >= BOGGLEDIM) {
			return false;
		}
		if (board[j][i]->isChecked())
			return false;
		return true;
	}

	// checks all the adjacent positions for new words
	void checkAdjacent(int i, int j, string& prefix) {
		struct coordinate {
			int x;
			int y;
		};
		coordinate positions[8] = { {i - 1, j - 1}, {i, j - 1}, {i + 1, j - 1}, {i + 1, j}, {i + 1, j + 1}, {i, j + 1}, {i - 1, j + 1}, {i - 1, j} };

		for (int a = 0; a < 8; a++) {
			if (checkWord(positions[a].x, positions[a].y, prefix)){
				string temp = prefix + board[positions[a].y][positions[a].x]->getLetter();
				if (bog->isWord(temp)) {

					bool found = false;

					for (int b = 0; b < foundWordsCount; b++) {
						if (foundWords[b].foundWord == temp) {
							found = true;
							foundWords[b].wordCount++;
						}
					}

					if (found == false) {
						cout << "Word: " << temp << endl;
						foundWords[foundWordsCount].foundWord = temp;
						foundWords[foundWordsCount].wordCount = 1;
						foundWordsCount++;
						if (showBoard == "y")
							printBoard();
					}
				}
				checkAdjacent(positions[a].x, positions[a].y, temp);
				board[positions[a].y][positions[a].x]->unCheck();
			}
		}

	}

	// checks to see if a substring is valid
	bool checkWord(int i, int j, string& prefix) {
		string word = prefix;
		if (letterBounds(i, j)) {
			word += board[j][i]->getLetter();
			if(bog->isPrefix(word))
				board[j][i]->setChecked();
			return bog->isPrefix(word);
		}
		else { return false; }
	}

	BoggleField* board[BOGGLEDIM][BOGGLEDIM];
	BoggleDict* bog;
	string showBoard;
	word foundWords[20];
	int foundWordsCount;
};

#endif