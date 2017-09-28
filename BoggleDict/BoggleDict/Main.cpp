/*
Andrew Maclean
May 11, 2017
Boggle Word Storage
*/

/*
	Andrew Maclean
	May 24, 2017

	Notes:
		This algorithm for checking words doesn't count for substrings of other words.
		If the word 'own' is in the table, then the algorithm can't find 'ow' because
		it has not reached the end of the three and therefore will not be a word. There
		are several words that will not be included in the game because of this.
*/

#include <iostream>
#include <string>
#include <fstream>
#include "WordTree.h"

using namespace std;

int main() {
	BoggleGame* game = new BoggleGame();

	//make a board of random letters
	//game->makeRandomBoard();

	//make a board of chosen letters
	game->makeBoard();

	//find all the words on the board
	game->findWords();

	system("pause");
	return 0;
}