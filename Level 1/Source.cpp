#include <iostream>
#include <random>
#include <vector>
#include <string>
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
void displayGameState(const std::vector<gamePieces>& gameBoard, bool revealMines) {
	// LINE 1
	std::cout << "   ";
	for(int i=0; i<gameBoardSize; i++) {
		std::cout << (i+1) << " ";
	}
	std::cout << std::endl;
	// OTHER LINES
	for(int row=0; row<gameBoardSize; row++) {
		std::cout << char('A'+row) << "| ";
		for(int col=0; col<gameBoardSize; col++) {
			switch(static_cast<int>(gameBoard.at(boardIndex(row, col)))) {
				case static_cast<int>(gamePieces::hiddenEmpty):
					std::cout << "-";
					break;
				case static_cast<int>(gamePieces::revealedEmpty):
					std::cout << countMines(row, col, gameBoard, gameBoardSize);
					break;
				case static_cast<int>(gamePieces::hiddenMine):
					std::cout << (revealMines ? "*" : "-");
					break;
				case static_cast<int>(gamePieces::revealedMine):
					std::cout << "*";
					break;
			}
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}
void displayGameDone(const std::vector<gamePieces>& gameBoard) {
	displayGameState(gameBoard, true);
	bool isWin;
	for(gamePieces gamePiece: gameBoard) {
		if(gamePiece == gamePieces::revealedMine) {
			isWin = false;
			goto RESULT; // break outer for
		}
	}
	RESULT:
	std::cout << (isWin ? "CONGRATULATIONS!  You won!" : "Better luck next time!") << std::endl;
}

/* Engine Functions*/
std::vector<gamePieces>& boardSetup(int gameBoardSize) {
    std::random_device seed;
    std::default_random_engine e(seed());
    std::bernoulli_distribution isMine(.25); // chance for a tile being a mine
	static std::vector<gamePieces> board(gameBoardSize*gameBoardSize);
	for(gamePieces piece: board) {
		piece = isMine(e) ? gamePieces::hiddenMine : gamePieces::hiddenEmpty; 
	}
	return board;
}
void changeGameState(std::vector<gamePieces>& gameBoard) {
	int row, col;
	bool end;
	do {
		do {
			std::cout << "Enter row: ";
			std::cin >> row;
			row -= 'A';
			std::cout << std::endl;
			std::cout << "Enter column: ";
			std::cin >> col;
			std::cout << "row=" << row << " col=" << col << std::endl;
		}
		while(row<0 || row>gameBoardSize || col <0 || col>gameBoardSize);
		end = true;
		switch(gameBoard.at(boardIndex(row, col))) {
			case gamePieces::hiddenEmpty:
				gameBoard.at(boardIndex(row, col)) = gamePieces::revealedEmpty;
				break;
			case gamePieces::hiddenMine:
				gameBoard.at(boardIndex(row, col)) = gamePieces::revealedMine;
				break;
			default:
				end = false;
		}
	}
	while(end);
	
}
bool isGameDone(const std::vector<gamePieces>& gameBoard) {
	bool revealedMine { false };
	bool hiddenEmpty { false };
	for(gamePieces gamePiece: gameBoard) {
		// NOTE: SWITCH USED FOR PERFORMANCE
		switch(gamePiece) {
			case gamePieces::revealedMine:
				return false; // return false from function as there is a revealed mine
			case gamePieces::hiddenEmpty:
				hiddenEmpty = true;
			default:
				; // empty
		}
	}
	return hiddenEmpty; // if false, then there are empty spaces; if true, then there are no revealed mines & hidden spaces
}

int countMines(int row, int column, const std::vector<gamePieces>& gameBoard, int gameBoardSize) {
	int count=0;
	for(int move_row=-1; move_row<2; move_row++) {
		for(int move_col=-1; move_col<2; move_col++) {
			if(row+move_row < 0 || row+move_row > gameBoardSize-1 || column+move_col < 0 || column+move_col > gameBoardSize-1)
				continue;
			switch(gameBoard.at(boardIndex(row+move_row, column+move_col))) {
				case gamePieces::hiddenMine:
					count++;
				case gamePieces::revealedMine:
					count++;
				default:
					; // empty
			}
		}
	}
	return count;
}
int boardIndex(int row, int column) {
	return row*gameBoardSize + column;
}