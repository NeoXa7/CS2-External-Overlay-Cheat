#pragma once
#include <Globals/hIncludes.h>
#define RED FOREGROUND_RED | FOREGROUND_INTENSITY
#define YELLOW FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE

void SetConsoleTextColor(WORD color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void CreateConsoleWindow(const wchar_t* title, int Width = 1000, int Height = 600)
{
	AllocConsole();
	FILE* file;
	freopen_s(&file, "CONOUT$", "w", stdout);  // Redirect stdout
	freopen_s(&file, "CONIN$", "r", stdin);   // Redirect stdin
	freopen_s(&file, "CONERR$", "w", stderr); // Redirect stderr

	SetConsoleTitle(title);

	HWND consoleWindow = GetConsoleWindow();
	if (consoleWindow != NULL)
	{
		MoveWindow(consoleWindow, 100, 100, Width, Height, TRUE);
	}
}

void DestroyConsoleWindow()
{
	HWND consoleWindow = GetConsoleWindow(); // Get the console window handle
	if (consoleWindow != NULL)
	{
		FreeConsole(); // Detach the console from the current process
		PostMessage(consoleWindow, WM_CLOSE, 0, 0); // Send a close message to the console window
	}
}


void CreateLogNotification(const string& LogsName,const string& logFileName) {
	std::time_t currentTime = std::time(nullptr);
	std::tm localTime;
	localtime_s(&localTime, &currentTime);

	cout
		<< " [INFO] "
		<< LogsName
		<< " Logs have been created at: "
		<< logFileName
		<< " ("
		<< std::put_time(&localTime, "%Y-%m-%d %H:%M:%S")
		<< ")"
		<< '\n';
	cout << '\n';
}