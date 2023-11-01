#pragma once
#include<iostream>
#include<string>
#include<windows.h>
#include"Ministry.h"
#include"EmpLogData.h"
#include"Commands.h"
namespace ms {
	class mm_Console {					//mm states for Main Menu
	public:
		void mm_helpCommand() {
			std::cout << "login - takes you to the log in window." << std::endl;
			std::cout << "exit - quits the application." << std::endl;
		}
		void mm_loginCommand(ms::Ministry &dataBase) {
			HANDLE hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			std::string id, password;
			std::cout << "Id: ";
			std::cin >> id;
			std::cout << "Password: ";
			std::cin >> password;
			ms::EmpLogData employee(0, "", "", "", "",0,'0');
			employee = dataBase.checkWho(id, password);
			if (employee.getId() == "") {
				SetConsoleTextAttribute(hConsole, 4);
				std::cout << "Wrong Id and/or Password! Please try again." << std::endl;
				SetConsoleTextAttribute(hConsole, 7);
			}
			else {
				bool nintendo = true;
				ms::Commands commands;
				SetConsoleTextAttribute(hConsole, 10);
				std::cout << "Logged in as " << employee.getName() << " " << employee.getSurname() << std::endl;
				if (employee.IsAdmin() == 0) {
					SetConsoleTextAttribute(hConsole, 14);
					std::cout << "You are an employee." << std::endl;
					std::cout << "If you want to check a list of commands available, just type 'help'" << std::endl;
					SetConsoleTextAttribute(hConsole, 7);
					while (nintendo) {
						std::string command;
						std::cout << "Command: ";
						std::cin >> command;
						if (command == "help") {
							SetConsoleTextAttribute(hConsole, 3);
							commands.all_helpCommand(employee);
							SetConsoleTextAttribute(hConsole, 7);
						}
						else if (command == "changepassword")
							commands.all_changePassword(employee, dataBase);
						else if (command == "addhours")
							commands.all_addHours(employee, dataBase);
						else if (command == "seehours") {
							SetConsoleTextAttribute(hConsole, 14);
							commands.all_seeHours(employee, dataBase);
							SetConsoleTextAttribute(hConsole, 7);
						}
						else if(command == "getpaid")
							commands.all_getPaid(employee, dataBase);
						else if (command == "logout") {
							SetConsoleTextAttribute(hConsole, 10);
							std::cout << "Logging out. See you soon " << employee.getName() << "." << std::endl;
							SetConsoleTextAttribute(hConsole, 7);
							nintendo = false;
						}
						else {
							SetConsoleTextAttribute(hConsole, 4);
							std::cout << "Unknown command." << std::endl;
							SetConsoleTextAttribute(hConsole, 7);
						}
					}
				}
				else if (employee.IsAdmin() == 1) {
					SetConsoleTextAttribute(hConsole, 14);
					std::cout << "You are an admin, you can interfere with the data base." << std::endl;
					std::cout << "If you want to check a list of commands available, just type 'help'" << std::endl;
					SetConsoleTextAttribute(hConsole, 7);
					int x = 0;
					for (auto i : dataBase.getDataBase()) {
						if (i.getPaymentApproval() == '1')
							x++;
					}
					if (x > 0) {
						SetConsoleTextAttribute(hConsole, 10);
						std::cout << "You have " << x << " pending payment approvals." << std::endl;
						SetConsoleTextAttribute(hConsole, 7);
					}
					while (nintendo) {
						std::string command;
						std::cout << "Command: ";
						std::cin >> command;
						if (command == "help") {
							SetConsoleTextAttribute(hConsole, 3);
							commands.all_helpCommand(employee);
							SetConsoleTextAttribute(hConsole, 7);
						}
						else if (command == "changepassword")
							commands.all_changePassword(employee, dataBase);
						else if (command == "addhours")
							commands.all_addHours(employee, dataBase);
						else if (command == "seehours") {
							SetConsoleTextAttribute(hConsole, 14);
							commands.all_seeHours(employee, dataBase);
							SetConsoleTextAttribute(hConsole, 7);
						}
						else if (command == "getpaid")
							commands.all_getPaid(employee, dataBase);
						else if (command == "hire")
							commands.adm_hireCommand(dataBase);
						else if (command == "fire")
							commands.adm_fireCommand(employee, dataBase);
						else if (command == "promote")
							commands.adm_promoteCommand(employee, dataBase);
						else if (command == "demote")
							commands.adm_demoteCommand(employee, dataBase);
						else if (command == "approve")
							commands.adm_approvePayment(dataBase);
						else if (command == "logout") {
							SetConsoleTextAttribute(hConsole, 10);
							std::cout << "Logging out. See you soon " << employee.getName() << "." << std::endl;
							SetConsoleTextAttribute(hConsole, 7);
							nintendo = false;
						}
						else {
							SetConsoleTextAttribute(hConsole, 4);
							std::cout << "Unknown command." << std::endl;
							SetConsoleTextAttribute(hConsole, 7);
						}
					}
				}
			}
		}
	};
}