#include <iostream>
#include <string>
#include "userBase.h"
#include "loginData.h"
#include "loggedCommands.h"
namespace ms {
	class Command {
	public:
		virtual void execute() = 0;
	};

	class loginCommand : public Command {
		std::string id;
		std::string password;
		ms::userBase userbase;
	public:
		loginCommand(const std::string& sentId, const std::string& sentPassword,const ms::userBase& sentUserbase) {
			id = sentId;
			password = sentPassword;
			userbase = sentUserbase;
		}
		virtual void execute() {
			std::vector<ms::loginData> base;
			base = userbase.getUsers();
			int checker = 0;
			int UI;
			for (int i = 0; i < base.size(); i++) {
				if (base[i].getId() == id && base[i].getPassword() == password) {
					checker++;
					UI = i;
				}
			}
			switch (checker) {
			case 0:
				std::cout << "Couldn't find a user with given id or password." << std::endl;
				break;
			case 1:
				std::cout << "Welcome " << base[UI].getName() <<" "<< base[UI].getSurname() << std::endl;
				bool switchh = true;
				ms::loggedCommand* ptr;
				while (switchh) {
					std::string command;
					std::cout << "Type in a command: ";
					std::cin >> command;
					if (command == "help") {
						ms::helpCommand hCmd;
						ptr = &hCmd;
						ptr->execute();
					}
					else if (command == "changepassword") {
						std::string newPassword1, newPassword2;
						std::cout << "New password: ";
						std::cin >> newPassword1;
						std::cout << "Repeat new password: ";
						std::cin >> newPassword2;
						if (newPassword1 == newPassword2) {
							ms::changepasswordCommand cpCmd(userbase, UI, newPassword1);
							ptr = &cpCmd;
							ptr->execute();
						}
						else
							std::cout << "Passwords do not match." << std::endl;
					}
					else if (command == "logout") {
						std::cout << "Logging out."<<std::endl;
						switchh = false;
					}
				}
				break;
			}
		}
	};
}