#include <iostream>
#include <random>
#include <vector>
#include <fstream>

/*Game Constants*/
const int gameBoardSize{ 10 };
enum class gamePieces { hiddenEmpty, revealedEmpty, hiddenMine, revealedMine };

/*GUI Functions*/
void splashScreen();
void displayGameState(const std::vector<gamePieces>& gameBoard, bool revealMines = false);
void displayGameDone(const std::vector<gamePieces>& gameBoard);

/* Engine Functions*/
std::vector<gamePieces>& boardSetup(int gameBoardSize);
void changeGameState(std::vector<gamePieces>& gameBoard);
bool isGameDone(const std::vector<gamePieces>& gameBoard);

int countMines(int row, int column, const std::vector<gamePieces>& gameBoard);
int boardIndex(int row, int column);

int main() {
	char playAgain{ 'y' };
	while (playAgain == 'y' || playAgain == 'Y')
	{
		std::vector<gamePieces>& gameBoard{ boardSetup(gameBoardSize) };
		while (!isGameDone(gameBoard))
		{
			displayGameState(gameBoard);
			changeGameState(gameBoard);
		}
		displayGameDone(gameBoard);
		std::cout << "\nDo you wish to play another game? (y/n): ";
		std::cin >> playAgain;
		
	}
}

/*GUI Functions*/
void splashScreen() {
	std::cout << "Mine Sweeper!" << std::endl;
	std::cout << std::endl;
	std::cout << "Your name here (2019)" << std::endl;
	std::cout << "CPSC 2377, Game Programming, Quest 0" << std::endl;
	std::cout << "UALR, Computer Science Dept." << std::endl;
	std::cout << std::endl;
	std::cout << "INSTRUCTIONS:" << std::endl;
	std::cout << std::endl;
	std::cout << "Clear the minefield without hitting a mine!" << std::endl;
	system("PAUSE");
}
void displayGameState(const std::vector<gamePieces>& gameBoard, bool revealMines = false);
void displayGameDone(const std::vector<gamePieces>& gameBoard);

/* Engine Functions*/
std::vector<gamePieces>& boardSetup(int gameBoardSize) {
	static std::vector<gamePieces> gamePieces(gameBoardSize);
	return gamePieces;
}
void changeGameState(std::vector<gamePieces>& gameBoard);
bool isGameDone(const std::vector<gamePieces>& gameBoard) {
	return false; // test
}