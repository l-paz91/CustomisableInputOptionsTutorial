// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Lets Learn - Customisable Input Options

	This is the initial console window program to get you started.
*/
// https://github.com/l-paz91/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <iostream>
#include <windows.h>
#include <vector>
#include <sstream>

using namespace std;

// -----------------------------------------------------------------------------

vector<bool> keys(5);
// https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
// 0x25 - ARROW LEFT
// 0x27 - ARROW RIGHT
// 0x28 - ARROW DOWN
// 0x26 - ARROW UP
// 0x1B - ESCAPE KEY

constexpr int gGridWidth = 60;
constexpr int gGridHeight = 30;
char gGameGrid[gGridHeight][gGridWidth];

int xPos = 15;
int yPos = 15;

bool gameover = false;

// -----------------------------------------------------------------------------

void drawGameGrid()
{
	system("CLS");

	stringstream ss;
	for (int i = 0; i < gGridWidth + 2; ++i)
	{
		ss << '.';
	}
	ss << '\n';

	// display the game grid
	for (int row = 0; row < gGridHeight; ++row)
	{
		ss << '.';
		for (int col = 0; col < gGridWidth; ++col)
		{
			ss << gGameGrid[row][col];
		}
		ss << '.';
		ss << '\n';
	}

	for (int i = 0; i < gGridWidth + 2; ++i)
	{
		ss << '.';
	}

	cout << ss.str();
}

// -----------------------------------------------------------------------------

int main()
{
	// resize console window
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 1000, 600, TRUE);

	for (int row = 0; row < gGridHeight; ++row)
	{
		for (int col = 0; col < gGridWidth; ++col)
		{
			gGameGrid[row][col] = ' ';
		}
	}

	gGameGrid[xPos][yPos] = 'A';

	drawGameGrid();

	while (!gameover)
	{
		// ---- input
		for (uint32_t k = 0; k < keys.size(); ++k)
		{
			keys[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x25\x27\x28\x26\x1B"[k]))) != 0;
		}

		// want to move left
		if (keys[0])
		{
			gGameGrid[xPos][yPos] = ' ';
			--yPos;
			if (yPos <= 0)
			{
				yPos = 0;
			}
			gGameGrid[xPos][yPos] = 'A';
			drawGameGrid();
		}

		// want to move right
		if (keys[1])
		{
			gGameGrid[xPos][yPos] = ' ';
			++yPos;
			if (yPos >= gGridWidth)
			{
				yPos = gGridWidth - 1;
			}
			gGameGrid[xPos][yPos] = 'A';
			drawGameGrid();
		}

		// want to move down
		if (keys[2])
		{
			gGameGrid[xPos][yPos] = ' ';
			++xPos;
			if (xPos >= gGridHeight)
			{
				xPos = gGridHeight - 1;
			}
			gGameGrid[xPos][yPos] = 'A';
			drawGameGrid();
		}

		// want to move up
		if (keys[3])
		{
			gGameGrid[xPos][yPos] = ' ';
			--xPos;
			if (xPos <= 0)
			{
				xPos = 0;
			}
			gGameGrid[xPos][yPos] = 'A';
			drawGameGrid();
		}

		// want to quit game loop
		if (keys[4])
		{
			gameover = true;
		}
	}

	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
