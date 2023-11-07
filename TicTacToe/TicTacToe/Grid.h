#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
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
		std::vector<std::vector<char>>getGrid() {
			return grid;
		}
		bool pushGrid(int r, int c, int player) {
			if (grid[r-1][c-1] == ' ') {
				if (player == 0) {
					grid[r-1][c-1] = 'X';
				}
				else if (player == 1) {
					grid[r-1][c-1] = 'O';
				}
				return true;
			}
			else {
				std::cout << "This place is already taken!" << std::endl;
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
	};
}