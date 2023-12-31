#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <fstream>

// Game Constants
int gameBoardSize;
float chanceMined;
enum class gamePieces { hiddenEmpty, revealedEmpty, hiddenMine, revealedMine };

// GUI Functions
void difficulty();
void splashScreen();
void displayGameState(const std::vector<gamePieces>& gameBoard, bool revealMines = false);
void displayGameDone(const std::vector<gamePieces>& gameBoard);
void clear(); // clear output

// Engine Functions
std::vector<gamePieces> boardSetup(int gameBoardSize);
void changeGameState(std::vector<gamePieces>& gameBoard);
bool isGameDone(const std::vector<gamePieces>& gameBoard);

int countMines(int row, int column, const std::vector<gamePieces>& gameBoard);
int boardIndex(int row, int column);

int main() {
	splashScreen();
	clear();
	difficulty();

	char playAgain{ 'y' };
	while (playAgain == 'y' || playAgain == 'Y') {
		std::vector<gamePieces> gameBoard = boardSetup(gameBoardSize);
		while (!isGameDone(gameBoard)) {
			displayGameState(gameBoard);
			changeGameState(gameBoard);
		}
		displayGameDone(gameBoard);
		std::cout << "\nDo you wish to play another game? (y/n): ";
		std::cin >> playAgain;
	}
}

// GUI Functions
////////////////////////////////////////////////////////////////////////////////
void splashScreen() {
	clear();
	std::cout << "Mine Sweeper!" << std::endl;
	std::cout << std::endl;
	std::cout << "Emmanuel Westra (2023)" << std::endl;
	std::cout << "CPSC 2377, Game Programming, Quest 0" << std::endl;
	std::cout << "UALR, Computer Science Dept." << std::endl;
	std::cout << std::endl;
	std::cout << "INSTRUCTIONS:" << std::endl;
	std::cout << "Clear the minefield without hitting a mine!" << std::endl;
	std::cout << "A number will identify the number of mines surrounding it (0-9)." << std::endl;
	std::cout << "Press any key to continue: ";
	std::cin.get();
}

void displayGameState(const std::vector<gamePieces>& gameBoard, bool revealMines) {
	clear();
	// LINE 1
	std::cout << "   ";
	for(int i=0; i<gameBoardSize; i++) {
		if(i>8) { // (i+1) >= 10
			std::cout << static_cast<char>('A'+i-9);
		}
		else {
			std::cout << i+1;
		}
		std::cout << " ";
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
					std::cout << countMines(row, col, gameBoard);
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
	std::cout << (isWin ? "CONGRATULATIONS!  YOU WON!" : "Better luck next time!") << std::endl;
}

// Engine Functions
////////////////////////////////////////////////////////////////////////////////
void difficulty() {
	char *choice = new char;
	do {
		std::cout << "Choose (e)asy [10x10, 25% mined], (m)edium [20x20 30% mined], (h)ard [30x30, 40% mined]: ";
		std::cin >> *choice;
		*choice = char(tolower(*choice));
	}
	while(*choice != 'e' && *choice != 'm' && *choice != 'h');
	switch(*choice) {
		case 'e':
			gameBoardSize = 10;
			chanceMined = 0.25f;
			return;
		case 'm':
			gameBoardSize = 20;
			chanceMined = 0.3f;
			return;
		case 'h':
			gameBoardSize = 30;
			chanceMined = 0.4f;
			return;
		default:
			return;
	}
}

std::vector<gamePieces> boardSetup(int gameBoardSize) {
    std::random_device seed;
    std::default_random_engine e(seed());
    std::bernoulli_distribution isMine(chanceMined); // chance for a tile being a mine
	std::vector<gamePieces> board(gameBoardSize*gameBoardSize);
	for(int i=0; i<board.size(); i++) {
		board.at(i) = isMine(e) ? gamePieces::hiddenMine : gamePieces::hiddenEmpty;
	}
	return board;
}

void changeGameState(std::vector<gamePieces>& gameBoard) {
	int row;
	int col;
	bool end;
	do {
		do {
			std::cout << "Enter row: ";
			char row_let;
			std::cin >> row_let;
			row_let = std::toupper(row_let); // convert to upper case
			row_let -= 'A'; // correction
			row = row_let;
			std::cout << "Enter column: ";
			std::cin >> col;
			--col;
		}
		while(row<0 || row>gameBoardSize || col <0 || col>gameBoardSize); // must be 
		end = true;
		switch(gameBoard.at(boardIndex(row, col))) {
			case gamePieces::hiddenEmpty:
				gameBoard.at(boardIndex(row, col)) = gamePieces::revealedEmpty;
				break;
			case gamePieces::hiddenMine:
				gameBoard.at(boardIndex(row, col)) = gamePieces::revealedMine;
				break;
			default:
				std::cout << (gameBoard.at(boardIndex(row, col))==gamePieces::revealedEmpty ? "Revealed square" : "Revealed mine") << std::endl;
				end = false;
		}
	}
	while(!end);
}

bool isGameDone(const std::vector<gamePieces>& gameBoard) {
	bool hiddenEmpty { false };
	for(gamePieces gamePiece: gameBoard) {
		// NOTE: SWITCH USED FOR PERFORMANCE
		switch(gamePiece) {
			case gamePieces::revealedMine:
				return true; // player failed
			case gamePieces::hiddenEmpty:
				hiddenEmpty = true;
				break;
			default:
				break;
		}
	}
	return !hiddenEmpty; // if false, then there are empty spaces; if true, then there are no revealed mines & hidden spaces
}

int countMines(int row, int column, const std::vector<gamePieces>& gameBoard) {
	int count=0;
	for(int move_row=-1; move_row<2; move_row++) {
		for(int move_col=-1; move_col<2; move_col++) {
			if(row+move_row < 0 || row+move_row >= gameBoardSize || column+move_col < 0 || column+move_col >= gameBoardSize)
				continue;
			switch(gameBoard.at(boardIndex(row+move_row, column+move_col))) {
				case gamePieces::hiddenMine:
					count++;
					break;
				case gamePieces::revealedMine:
					count++;
					break;
				default:
					break;
			}
		}
	}
	return count;
}

int boardIndex(int row, int column) {
	return row*gameBoardSize + column;
}

void clear() {
	// \033[2J to clear console; \033[H clears console and returns cursor to home (I had dissues with it clearing output, so I used both)
	std::cout << "\033[2J\033[H";
}