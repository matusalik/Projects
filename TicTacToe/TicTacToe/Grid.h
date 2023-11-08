#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
namespace ms {
	class Grid {
		std::vector<std::vector<char>>grid;
	public:
		Grid() {
			for (int i = 0; i < 3; i++) {
				std::vector<char>temp;
				for (int j = 0; j < 3; j++) {
					temp.push_back(' ');
				}
				grid.push_back(temp);
			}
		}
		bool isDigit(std::string str) {
			for (int i = 0; i < str.length(); i++) {
				if (isdigit(str[i]) == false) {
					return false;
				}
				return true;
			}
		}
		bool pushGrid(std::string sr, std::string sc, int player) {
			if (isDigit(sr)&&isDigit(sc)) {
				int r = std::stoi(sr);
				int c = std::stoi(sc);
				if (grid[r - 1][c - 1] == ' ') {
					if (player == 0) {
						grid[r - 1][c - 1] = 'X';
					}
					else if (player == 1) {
						grid[r - 1][c - 1] = 'O';
					}
					return true;
				}
				else {
					std::cout << "This place is already taken!" << std::endl;
					return false;
				}
			}
			else {
				std::cout << "Invalid input!" << std::endl;
				return false;
			}
		}
		void showGrid() {
			std::cout << "-------------" << std::endl;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					switch (j) {
					case 0:
						std::cout << "|" << grid[i][j] << std::setw(3) << "|";
						break;
					case 1:
						std::cout << std::setw(3) << grid[i][j] << "|";
						break;
					case 2:
						std::cout << std::setw(3) << grid[i][j] << "|";
					}
				}
				std::cout << std::endl;
				std::cout << "-------------"<<std::endl;
			}
		}
		bool isFull() {
			int counter = 0;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (grid[i][j] != ' ') {
						counter++;
					}
				}
			}
			if (counter == 9) {
				return false;
			}
			return true;
		}
		int checkWinner() {
			for (int i = 0; i < 3; i++) {
				int x = 0, o = 0;
				for (int j = 0; j < 3; j++) {
					if (grid[i][j] == 'X')
						x++;
					else if (grid[i][j] == 'O')
						o++;
				}
				if (x == 3)
					return 0;
				else if (o == 3)
					return 1;
			}
			for (int i = 0; i < 3; i++) {
				int x = 0, o = 0;
				for (int j = 0; j < 3; j++) {
					if (grid[j][i] == 'X')
						x++;
					else if (grid[j][i] == 'O')
						o++;
				}
				if (x == 3)
					return 0;
				else if (o == 3)
					return 1;
			}
			if (grid[0][0] == 'X' && grid[1][1] == 'X' && grid[2][2] == 'X') {
				return 0;
			}
			if (grid[0][0] == 'O' && grid[1][1] == 'O' && grid[2][2] == 'O') {
				return 1;
			}
			if (grid[0][2] == 'X' && grid[1][1] == 'X' && grid[2][0] == 'X') {
				return 0;
			}
			if (grid[0][2] == 'O' && grid[1][1] == 'O' && grid[2][0] == 'O') {
				return 1;
			}
			return 2;
		}
		void clearConsole() {
			COORD topLeft = { 0, 0 };
			HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
			CONSOLE_SCREEN_BUFFER_INFO screen;
			DWORD written;
			GetConsoleScreenBufferInfo(console, &screen);
			FillConsoleOutputCharacterA(
				console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
			);
			FillConsoleOutputAttribute(
				console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
				screen.dwSize.X * screen.dwSize.Y, topLeft, &written
			);
			SetConsoleCursorPosition(console, topLeft);
		}
	};
}