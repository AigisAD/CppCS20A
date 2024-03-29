#include <iostream>
#include "utils.h"
void report() {
	std::string msg = "\nTo make World only have one grid as a member variable and none others, \n"
		"you could make World method \"updateWorld\" have a local multi-dimensional array that \"deep\" copies \n"
		"the contents of the member grid right at the start. Then you can pass that array to method \n"
		"getNextState as the \"second\" grid. The local array will hold the current day and won't change \n"
		"until the member grid is updated. Doing this allows us to delete a lot of code in the World\n"
		"methods that look at the second member grid. To summarize: Make a local array in updateWorld thats copies the \n"
		"member grid at the start and goes to getNextState to give the next day info to the member grid."; // Replace Hello World with your answer.
	std::cout << msg << std::endl;
}

//
// Do NOT modify any code found below this warning.  Note that moving code is not the same
// thing as modifying code.  Modifying code changes the behavior, moving code does not. 
// 

#include <chrono>
#include <thread>

void delay(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}


///////////////////////////////////////////////////////////////////////////
//  ClearScreen Implementation
///////////////////////////////////////////////////////////////////////////


// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	COORD upperLeft = { 0, 0 };
	DWORD dwCharsWritten;
	FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
		&dwCharsWritten);
	SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
void clearScreen()  // will just write a newline in an Xcode output window
{
	static const char* term = getenv("TERM");
	if (term == nullptr || strcmp(term, "dumb") == 0)
		cout << endl;
	else
	{
		static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
		cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
	}
}

#endif