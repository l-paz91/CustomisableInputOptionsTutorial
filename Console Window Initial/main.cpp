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
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <vector>
#include <sstream>

using namespace std;

// -----------------------------------------------------------------------------

vector<bool> gKeys(5);
// https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
// 0x25 - ARROW LEFT
// 0x27 - ARROW RIGHT
// 0x28 - ARROW DOWN
// 0x26 - ARROW UP
// 0x1B - ESCAPE KEY

constexpr int gGridWidth = 60;
constexpr int gGridHeight = 30;
constexpr char gSymbol = -2;
char gGameGrid[gGridHeight][gGridWidth];

int g_xPos = 15;
int g_yPos = 15;

bool gGameover = false;

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

	gGameGrid[g_xPos][g_yPos] = gSymbol;

	drawGameGrid();

	while (!gGameover)
	{
		// ---- input
		for (uint32_t k = 0; k < gKeys.size(); ++k)
		{
			gKeys[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x25\x27\x28\x26\x1B"[k]))) != 0;
		}

		// want to move left
		if (gKeys[0])
		{
			gGameGrid[g_xPos][g_yPos] = ' ';
			--g_yPos;
			if (g_yPos < 0)
			{
				g_yPos = 0;
			}
			else
			{
				gGameGrid[g_xPos][g_yPos] = gSymbol;
				drawGameGrid();
			}
		}

		// want to move right
		if (gKeys[1])
		{
			gGameGrid[g_xPos][g_yPos] = ' ';
			++g_yPos;
			if (g_yPos >= gGridWidth)
			{
				g_yPos = gGridWidth - 1;
			}
			else
			{
				gGameGrid[g_xPos][g_yPos] = gSymbol;
				drawGameGrid();
			}
		}

		// want to move down
		if (gKeys[2])
		{
			gGameGrid[g_xPos][g_yPos] = ' ';
			++g_xPos;
			if (g_xPos >= gGridHeight)
			{
				g_xPos = gGridHeight - 1;
			}
			else
			{
				gGameGrid[g_xPos][g_yPos] = gSymbol;
				drawGameGrid();
			}
		}

		// want to move up
		if (gKeys[3])
		{
			gGameGrid[g_xPos][g_yPos] = ' ';
			--g_xPos;
			if (g_xPos < 0)
			{
				g_xPos = 0;
			}
			else
			{
				gGameGrid[g_xPos][g_yPos] = gSymbol;
				drawGameGrid();
			}
		}

		// want to quit game loop
		if (gKeys[4])
		{
			gGameover = true;
		}
	}

	_getch();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
