#include <iostream>
#include<windows.h>
#include"Grid.h"
int main()
{
    ms::Grid grid;
    bool Switch=true,Switch2=true;
    int counter = 0;
    char game;
    std::cout << "Welcome to TicTacToe!" << std::endl;
    std::cout << "Please choose if you want to play against a computer or with a friend." << std::endl;
    while (Switch2) {
        std::cout << "Type 'C' for computer or 'F' for a game with a friend." << std::endl;
        std::cin >> game;
        if (game == 'C') {
            Switch2 = false;
        }
        else if (game == 'F') {
            grid.clearConsole();
            grid.showGrid();
            while (Switch) {
                int r, c;
                if (counter % 2 == 0) {
                    std::cout << "|Player One (X)|" << std::endl;
                    std::cout << "Row: ";
                    std::cin >> r;
                    std::cout << "Collumn: ";
                    std::cin >> c;
                    grid.clearConsole();
                    if (grid.pushGrid(r, c, 0)) {
                        counter++;
                    }
                }
                else if (counter % 2 != 0) {
                    std::cout << "|Player Two (O)|" << std::endl;
                    std::cout << "Row: ";
                    std::cin >> r;
                    std::cout << "Collumn: ";
                    std::cin >> c;
                    grid.clearConsole();
                    if (grid.pushGrid(r, c, 1)) {
                        counter++;
                    }
                }
                grid.showGrid();
                if (grid.checkWinner() == 0) {
                    std::cout << "Player One wins!" << std::endl;
                    Switch = false;
                }
                else if (grid.checkWinner() == 1) {
                    std::cout << "Player Two wins!" << std::endl;
                    Switch = false;
                }
                else if (grid.checkWinner() == 2) {
                    Switch = grid.isFull();
                }
            }
            Switch2 = false;
        }
        else {
            std::cout << "That's neither 'C' nor 'F'!" << std::endl;
        }
    }
    if (counter == 9) {
        std::cout << "Game finished with a draw!" << std::endl;
    }
}
