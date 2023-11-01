#pragma once
#include<vector>
#include<fstream>
#include<sstream>
#include<iostream>
#include "loginData.h"
namespace ms {
	class userBase {
		std::vector<ms::loginData> users;
	public:


		std::vector<ms::loginData> getUsers() const noexcept {
			return users;
		}

		void downloadUsers() {
			std::ifstream data;
			data.open("base.txt");
			if (data.is_open()) {
				std::vector<std::string> allusers;
				std::vector<std::vector<std::string>> usersVec;
				std::string temp;
				while (std::getline(data, temp))
					allusers.push_back(temp);
				for (int i = 0; i < allusers.size(); i++) {
					std::vector<std::string> oneuser;
					std::string aloneData;
					std::istringstream iss(allusers[i]);
					while (std::getline(iss, aloneData, ' '))
						oneuser.push_back(aloneData);
					usersVec.push_back(oneuser);
				}
				for (int i = 0; i < usersVec.size(); i++) {
					std::vector<std::string> temp;
					temp = usersVec[i];
					int isAdmin = std::stoi(temp[0]);
					double zloty = std::stod(temp[3]);
					double euro = std::stod(temp[4]);
					double dolar = std::stod(temp[5]);
					ms::Account balance(zloty, euro, dolar);
					users.push_back(ms::loginData(isAdmin, temp[1], temp[2], balance, temp[6], temp[7]));
				}
				data.close();
			}
			else {
				std::cout << "Couldn't open the file!" << std::endl;
			}
		}

		void rewriteDataBase(std::vector<ms::loginData> sentUsers) {
			users = sentUsers;
			std::ofstream ofs("base.txt", std::ofstream::trunc);									
			for (int i = 0; i < users.size(); i++) {													
				std::string newUserStr, isAdminStr,zlotyStr,euroStr,dolarStr;
				ms::loginData temp = users[i];
				ms::Account balance = users[i].getBalance();
				zlotyStr = std::to_string(balance.getZloty());
				euroStr = std::to_string(balance.getEuro());
				dolarStr = std::to_string(balance.getDolar());
				isAdminStr = std::to_string(temp.getIsAdmin());											
				newUserStr = isAdminStr + " " + temp.getName() + " " + temp.getSurname() +
					" " + zlotyStr + " " + euroStr + " " + dolarStr + " " + temp.getId() +
					" " + temp.getPassword() + "\n";
				ofs << newUserStr;																	
			}
			ofs.close();
		}
	};
}
