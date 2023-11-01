#pragma once
#include<iostream>
#include<string>
#include"Ministry.h"
namespace ms {
	class Commands {															
	public:
		bool findId(std::vector<std::string>idVector,std::string id) {				//method for checking if employee with given id exists in database
			if (std::find(idVector.begin(), idVector.end(), id) != idVector.end())
				return true;
			else
				return false;
		}
		std::string generateId(ms::Ministry dataBase) {							//id generator
			std::vector<ms::EmpLogData>employees = dataBase.getDataBase();		//getting database vector from ms::Ministry object
 			int n = (employees.size()-1);										//checking the amount of employees
			std::string latestIdStr = employees[n].getId();						//getting id from latest hired employee
			int latestIdInt = std::stoi(latestIdStr);							//converting latest id from string to int so we can incremate it
			latestIdInt++;														//incremating latest id
			std::string newEmployeeId = std::to_string(latestIdInt);			//assigning incremated id to new employees id	
			return newEmployeeId;
		}
		std::string generatePassword() {										//random password generator
			std::string baseLower = "abcdefghijklmnopqrstuvwxyz";				//base of letters for generating password
			std::string baseUpper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
			std::string finalPassword;
			srand((unsigned)time(NULL));										//providing new key, otherwise generator will generate similar numbers every compilation
			for (int i = 0; i < 10; i++) {
				int numberOrLetter = rand() % 3;								//drawing if next character in password should be letter or number
				if (numberOrLetter == 0) {										//letter
					int randLetter = rand() % 26;								//drawing number between 0 and 25 and choosing right letter from lowercase base
					finalPassword = finalPassword + baseLower[randLetter];
				}
				else if (numberOrLetter == 1) {
					int randLetter = rand() % 26;								//drawing number between 0 and 25 and choosing right letter from uppercase base
					finalPassword = finalPassword + baseUpper[randLetter];
				}
				else {															//number
					int randNumber = rand() % 10;								//drawing number between 0 and 9
					std::string tempNumber = std::to_string(randNumber);
					finalPassword = finalPassword + tempNumber;
				}
			}
			return finalPassword;
		}
		bool isNumber(std::string hours) {
			int x=0;
			for (int i=0; i < hours.size(); i++) {
				if ((hours[i] >= 48 && hours[i] <= 57)|| hours[i] == '.')
					x++;
			}
			if (x == hours.size())
				return true;
			else
				return false;
		}

		// COMMANDS AVAILABLE ONLY FOR ADMINS
		void adm_hireCommand(ms::Ministry &dataBase) {
			HANDLE hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 14);
			std::cout << "You are going to hire new employee, please insert his/her name and surname." << std::endl;
			std::cout << "Employee's new Id and password will be generated automatically." << std::endl;
			SetConsoleTextAttribute(hConsole, 7);
			std::string name, surname;
			std::cout << "Name: ";
			std::cin >> name;
			std::cout << "Surname: ";
			std::cin >> surname;
			std::string id = generateId(dataBase);
			std::string password = generatePassword();
			dataBase.hireEmployee(id,name,surname,password);
			SetConsoleTextAttribute(hConsole, 10);
			std::cout << "You've just hired new employee!"<<std::endl;
			SetConsoleTextAttribute(hConsole, 7);
		}
		void adm_fireCommand(ms::EmpLogData employee, ms::Ministry &dataBase) {
			HANDLE hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 14);
			std::cout << "You are going to fire employee, please insert employee's Id."<<std::endl;
			SetConsoleTextAttribute(hConsole, 7);
			std::string id;
			std::cout << "Id: ";
			std::cin >> id;
			if (id != employee.getId()) {
				std::vector<std::string>idVector = dataBase.getIdVector();
				bool x = findId(idVector, id);
				if (x == true) {
					dataBase.fireEmployee(id);
					SetConsoleTextAttribute(hConsole, 10);
					std::cout << "You've just fired an employee." << std::endl;
					SetConsoleTextAttribute(hConsole, 7);
				}
				else {
					SetConsoleTextAttribute(hConsole, 4);
					std::cout << "Couldn't find an employee with given id, please try again." << std::endl;
					SetConsoleTextAttribute(hConsole, 7);
				}
			}
			else {
				SetConsoleTextAttribute(hConsole, 4);
				std::cout << "You can't fire yourself!" << std::endl;
				SetConsoleTextAttribute(hConsole, 7);
			}
		}
		void adm_promoteCommand(ms::EmpLogData employee, ms::Ministry &dataBase) {
			HANDLE hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 14);
			std::cout << "You are going to promote an employee,please insert employee's Id." << std::endl;
			SetConsoleTextAttribute(hConsole, 7);
			std::string id;
			std::cout << "Id: ";
			std::cin >> id;
			if (id != employee.getId()) {
				std::vector<std::string>idVector = dataBase.getIdVector();
				bool x = findId(idVector, id);
				if (x == true) {
					try {
						dataBase.promoteEmployee(id);
						SetConsoleTextAttribute(hConsole, 10);
						std::cout << "You've just promoted an employee." << std::endl;
						SetConsoleTextAttribute(hConsole, 7);
					}
					catch (const char* msg) {
						SetConsoleTextAttribute(hConsole, 4);
						std::cerr << msg << std::endl;
						SetConsoleTextAttribute(hConsole, 7);
					}
				}
				else {
					SetConsoleTextAttribute(hConsole, 4);
					std::cout << "Couldn't find an employee with given id, please try again." << std::endl;
					SetConsoleTextAttribute(hConsole, 7);
				}
			}
			else {
				SetConsoleTextAttribute(hConsole, 4);
				std::cout << "You can't promote yourself!" << std::endl;
				SetConsoleTextAttribute(hConsole, 7);
			}
		}
		void adm_demoteCommand(ms::EmpLogData employee, ms::Ministry &dataBase) {
			HANDLE hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 14);
			std::cout << "You are going to demote an employee, please insert employee's Id." << std::endl;
			SetConsoleTextAttribute(hConsole, 7);
			std::string id;
			std::cout << "Id: ";
			std::cin >> id;
			if (id != employee.getId()) {
				std::vector<std::string>idVector = dataBase.getIdVector();
				bool x = findId(idVector, id);
				if (x == true) {
					try {
						dataBase.demoteEmployee(id);
						SetConsoleTextAttribute(hConsole, 10);
						std::cout << "You've just demoted an employee." << std::endl;
						SetConsoleTextAttribute(hConsole, 7);
					}
					catch (const char* msg) {
						SetConsoleTextAttribute(hConsole, 4);
						std::cerr << msg << std::endl;
						SetConsoleTextAttribute(hConsole, 7);
					}
				}
				else {
					SetConsoleTextAttribute(hConsole, 4);
					std::cout << "Couldn't find an employee with given id, please try again." << std::endl;
					SetConsoleTextAttribute(hConsole, 7);
				}
			}
			else {
				SetConsoleTextAttribute(hConsole, 4);
				std::cout << "Yout can't demote yourself!" << std::endl;
				SetConsoleTextAttribute(hConsole, 7);
			}
		}
		void adm_approvePayment(ms::Ministry &dataBase) {
			HANDLE hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 14);
			std::cout << "You are going to approve employee's request for payment, please insert employee's Id." << std::endl;
			SetConsoleTextAttribute(hConsole, 7);
			std::string id;
			std::cout << "Id: ";
			std::cin >> id;
			std::vector<std::string>idVector = dataBase.getIdVector();
			bool x = findId(idVector, id);
			if (x == true) {
				try {
					dataBase.approvePayment(id);
					SetConsoleTextAttribute(hConsole, 10);
					std::cout << "You've just approved employee's payment." << std::endl;
					SetConsoleTextAttribute(hConsole, 7);
				}
				catch (const char* msg) {
					SetConsoleTextAttribute(hConsole, 4);
					std::cerr << msg << std::endl;
					SetConsoleTextAttribute(hConsole, 7);
				}
			}
			else {
				SetConsoleTextAttribute(hConsole, 4);
				std::cout << "Couldn't find an employee with given id, please try again." << std::endl;
				SetConsoleTextAttribute(hConsole, 7);
			}
		}

		// COMMANDS AVAILABLE FOR EVERYBODY
		void all_helpCommand(ms::EmpLogData employee) {
			if (employee.IsAdmin() == 1) {
				std::cout << "logout - logs you out off your accont and takes you to the main menu." << std::endl;
				std::cout << "changepassword - changes your password." << std::endl;
				std::cout << "addhours - adds the amount of hours you worked on a given day." << std::endl;
				std::cout << "seehours - shows you how many hours you've worked since last payment." << std::endl;
				std::cout << "getpaid - counts how much money you've earned and sends bank transfer to your account." << std::endl;
				std::cout << "approve - approves employee's payment request." << std::endl;
				std::cout << "hire - adds a new employee to the database." << std::endl;
				std::cout << "fire - deletes chosen employee from the database" << std::endl;
				std::cout << "promote - makes employee an admin" << std::endl;
				std::cout << "demote - makes admin a regular employee" << std::endl;
			}
			if (employee.IsAdmin() == 0) {
				std::cout << "logout - logs you out off your accont and takes you to the main menu." << std::endl;
				std::cout << "changepassword - changes your password." << std::endl;
				std::cout << "addhours - adds the amount of hours you worked on a given day." << std::endl;
				std::cout << "seehours - shows you how many hours you've worked since last payment." << std::endl;
				std::cout << "getpaid - counts how much money you've earned and sends bank transfer to your account." << std::endl;
			}
		}
		void all_changePassword(ms::EmpLogData &employee,ms::Ministry &dataBase) {
			HANDLE hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			bool nintendo = true;
			while (nintendo) {
				SetConsoleTextAttribute(hConsole, 14);
				std::cout << "You are going to change you password."<<std::endl;
				SetConsoleTextAttribute(hConsole, 7);
				std::string newPassword1, newPassword2;
				std::cout << "New password: ";
				std::cin >> newPassword1;
				std::cout << "Repeat password: ";
				std::cin >> newPassword2;
				if (newPassword1 == newPassword2) {
					dataBase.changePassword(newPassword1, employee.getId());
					SetConsoleTextAttribute(hConsole, 10);
					std::cout << "You've just changed your password." << std::endl;
					SetConsoleTextAttribute(hConsole, 7);
					nintendo = false;
				}
				else {
					SetConsoleTextAttribute(hConsole, 4);
					std::cout << "Given passwords are different. Please try again." << std::endl;
					SetConsoleTextAttribute(hConsole, 7);
				}
			}
		}
		void all_addHours(ms::EmpLogData &employee, ms::Ministry &dataBase) {
			HANDLE hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			std::string hours;
			SetConsoleTextAttribute(hConsole, 14);
			std::cout << "How many hours have you been working today: ";
			SetConsoleTextAttribute(hConsole, 7);
			std::cin >> hours;
			bool x = isNumber(hours);
			if (x == true) {
				double hoursDbl = std::stod(hours);
				dataBase.addHours(hoursDbl, employee.getId());
				SetConsoleTextAttribute(hConsole, 10);
				std::cout << "Hours added to your account." << std::endl;
				SetConsoleTextAttribute(hConsole, 7);
			}
			else {
				SetConsoleTextAttribute(hConsole, 4);
				std::cout << "Given value does not fit to describe amount of hours." << std::endl;
				SetConsoleTextAttribute(hConsole, 7);
			}
		}
		void all_seeHours(ms::EmpLogData employee, ms::Ministry dataBase) {
			double x = dataBase.seeHours(employee.getId());
			std::cout << "You worked " << x << " hours since last payment." << std::endl;
		}
		void all_getPaid(ms::EmpLogData &employee, ms::Ministry &dataBase) {
			HANDLE hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			if (employee.IsAdmin() == 1) {
				double x = dataBase.getPaid(employee.getId());
				SetConsoleTextAttribute(hConsole, 14);
				std::cout << "You've earned " << x << " pounds." << std::endl;
				SetConsoleTextAttribute(hConsole, 10);
				std::cout << "Bank transfer should appear on your account soon." << std::endl;
				SetConsoleTextAttribute(hConsole, 7);
			}
			else if (employee.IsAdmin() == 0) {
				double x = dataBase.getPaid(employee.getId());
				SetConsoleTextAttribute(hConsole, 14);
				std::cout << "You've earned " << x << " pounds." << std::endl;
				dataBase.waitForApproval(employee.getId());
				SetConsoleTextAttribute(hConsole, 10);
				std::cout << "Since you are an employee, you have to wait for admin to approve your request." << std::endl;
				std::cout << "As soon as admin approves your request, bank transfer should appear on your bank account." << std::endl;
				SetConsoleTextAttribute(hConsole, 7);
			}
		}
	};
}
