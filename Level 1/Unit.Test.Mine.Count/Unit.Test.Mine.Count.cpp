#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
const int gameBoardSize = 10;
enum class gamePieces { hiddenEmpty, revealedEmpty, hiddenMine, revealedMine };
int countMines(int row, int column, const std::vector<gamePieces>& gameBoard);
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestMineCount
{
	TEST_CLASS(UnitTestMineCount)
	{
	public:
		
		TEST_METHOD(MineCount)
		{
			
			std::vector<gamePieces> gameBoard(gameBoardSize*gameBoardSize);
			for (auto& slot : gameBoard)
			{
				slot = gamePieces::hiddenMine;
			};

			int numMines{ countMines(2, 2, gameBoard) };
			Assert::AreEqual(numMines, 8);
			numMines = countMines(0, 0, gameBoard);
			Assert::AreEqual(numMines, 3);
			numMines = countMines(0, gameBoardSize-1, gameBoard);
			Assert::AreEqual(numMines, 3);
			numMines = countMines(gameBoardSize - 1, gameBoardSize - 1, gameBoard);
			Assert::AreEqual(numMines, 3);
			numMines = countMines(1, gameBoardSize - 1, gameBoard);
			Assert::AreEqual(numMines, 5);
		}
	};
}
