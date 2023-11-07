#include <iostream>
#include<windows.h>
#include"Grid.h"
BOOL cls()
{
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hConsoleOutput, &csbi))
    {
        CHAR_INFO fi = { ' ', csbi.wAttributes };
        csbi.srWindow.Left = 0;
        csbi.srWindow.Top = 0;
        csbi.srWindow.Right = csbi.dwSize.X - 1;
        csbi.srWindow.Bottom = csbi.dwSize.Y - 1;
        return ScrollConsoleScreenBufferW(hConsoleOutput, &csbi.srWindow, 0, csbi.dwSize, &fi);
    }
    return FALSE;
}
int main()
{
    ms::Grid grid;
    bool Switch=true;
    int counter = 0;
    grid.showGrid();
    while (Switch) {
        int r, c;
        if (counter % 2 == 0) {
            std::cout << "|Player One|" << std::endl;
            std::cout << "Row: ";
            std::cin >> r;
            std::cout << "Collumn: ";
            std::cin >> c;
            if (grid.pushGrid(r, c, 0)) {
                counter++;
            }
        }
        else if (counter % 2 != 0) {
            std::cout << "|Player Two|" << std::endl;
            std::cout << "Row: ";
            std::cin >> r;
            std::cout << "Collumn: ";
            std::cin >> c;
            if (grid.pushGrid(r, c, 1)) {
                counter++;
            }
        }
        grid.showGrid();
        Switch = grid.isFull();
    }   
}
