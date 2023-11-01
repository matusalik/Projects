#include "userBase.h"
#include "Commands.h"
#include <iostream>
#include<vector>
#include<string>
int main()
{
	ms::userBase base;
	base.downloadUsers();
	std::vector<ms::loginData>users = base.getUsers();
	std::cout << "Welcome to our cantor!"<<std::endl;
	std::cout << "Please type in 'login' if u want to log in or 'exit' if u want to exit our application" << std::endl;
	ms::Command* ptr;
	bool flick = true;
	while (flick) {
		std::string command;
		std::cin >> command;
		if (command == "login") {
			std::string login, password;
			std::cout << "Login: ";
			std::cin >> login;
			std::cout << "Password: ";
			std::cin >> password;
			ms::loginCommand lCmd(login, password, base);
			ptr = &lCmd;
			ptr->execute();

		}
		else if (command == "exit") {
			flick = false;
		}	
		else {
			std::cout << "Unknown command!" << std::endl;
		}
	}
}
