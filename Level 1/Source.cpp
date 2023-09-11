#include <iostream>
#include <random>
#include <vector>
#include <fstream>

/*Game Constants*/
const int gameBoardSize{ 10 };
enum class gamePieces { hiddenEmpty, revealedEmpty, hiddenMine, revealedMine };

/*GUI Functions*/
void splashScreen();
void displayGameState(const std::vector<gamePieces>& gameBoard, bool revealMines = false, const int gameBoardSize);
void displayGameDone(const std::vector<gamePieces>& gameBoard);

/* Engine Functions*/
std::vector<gamePieces>& boardSetup(int gameBoardSize);
void changeGameState(std::vector<gamePieces>& gameBoard);
bool isGameDone(const std::vector<gamePieces>& gameBoard);

int countMines(int row, int column, const std::vector<gamePieces>& gameBoard, int gameBoardSize);
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
void displayGameState(const std::vector<gamePieces>& gameBoard, bool revealMines, const int gameBoardSize) {
	// LINE 1
	std::cout << "   ";
	for(int i=0; i<gameBoardSize; i++) {
		std::cout << (i+1) << " ";
	}
	std::cout << std::endl;
	// OTHER LINES
	for(int row=0; row<gameBoardSize; row++) {
		std::cout << ('A'+row) << "| ";
		for(int col=0; col<gameBoardSize; col++) {
			switch(static_cast<int>(gameBoard.at(row*gameBoardSize+col))) {
				case static_cast<int>(gamePieces::hiddenEmpty):
					std::cout << "-";
					break;
				case static_cast<int>(gamePieces::revealedEmpty):
					std::cout << countMines(row, col, gameBoard, gameBoardSize);
					break;
				case static_cast<int>(gamePieces::hiddenMine):
					std::cout << revealMines? "*" : "-";
					break;
				case static_cast<int>(gamePieces::revealedMine):
					std::cout << "*";
					break;
			}
			std::cout << " ";
		}
	}
}
void displayGameDone(const std::vector<gamePieces>& gameBoard) {

}

/* Engine Functions*/
std::vector<gamePieces>& boardSetup(int gameBoardSize) {
	// random
    std::random_device seed;
    std::default_random_engine e(seed());
    std::bernoulli_distribution isMine(.25); // chance for a tile being a mine
	static std::vector<gamePieces> board(gameBoardSize);
	for(gamePieces piece: board) {
		piece = isMine(e) ? gamePieces::hiddenMine : gamePieces::hiddenEmpty; 
	}
	return board;
}
void changeGameState(std::vector<gamePieces>& gameBoard) {
	
}
bool isGameDone(const std::vector<gamePieces>& gameBoard) {
	return false; // test
}

int countMines(int row, int column, const std::vector<gamePieces>& gameBoard, int gameBoardSize) {
	return 1;
}
int boardIndex(int row, int column) {
	return 1;
}