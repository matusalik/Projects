#include <iostream>
#include"Employee.h"
#include"EmpLogData.h"
#include"Ministry.h"
#include"mm_Console.h"

int main()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ms::mm_Console mm_console;						//Constructs an object of ms::Console
	std::vector<ms::EmpLogData>base;				//Creates ms::EmpLogData vector
	ms::Ministry dataBase(base);					//Constructs an object of ms::Ministry
	try {
		dataBase.downloadDataBase();					//Fills the object with desired database
		bool nintendo = true;								//that's a switch which states whether the loop should still be looping or not

		SetConsoleTextAttribute(hConsole, 14);
		std::cout << "Welcome to the Ministry of magic." << std::endl;
		std::cout << "Type 'help' to see the full list of commands available." << std::endl;
		SetConsoleTextAttribute(hConsole, 7);
		while (nintendo) {
			std::cout << "Command: ";
			std::string command;
			std::cin >> command;
			if (command == "help") {
				SetConsoleTextAttribute(hConsole, 3);
				mm_console.mm_helpCommand();
				SetConsoleTextAttribute(hConsole, 7);
			}
			else if (command == "login")
				mm_console.mm_loginCommand(dataBase);
			else if (command == "exit")
				nintendo = false;
			else {
				SetConsoleTextAttribute(hConsole, 4);
				std::cout << "Unknown command." << std::endl;
				SetConsoleTextAttribute(hConsole, 7);
			}
		}
		base.clear();
	}
	catch (const char* msg) {
		SetConsoleTextAttribute(hConsole, 4);
		std::cerr << msg << std::endl;
		SetConsoleTextAttribute(hConsole, 7);
	}
}
