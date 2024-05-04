#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <iomanip>
#include <set>
#include <algorithm>
#include "menu.h"
#pragma warning(disable: 4996)

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	menu();
	std::cout << "До встречи!\n";
	return 0;
}