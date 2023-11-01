#pragma once
#include "EmpLogData.h"
#include "Employee.h"
#include<vector>
#include<fstream>
#include<sstream>
namespace ms {
	class Ministry {
		std::vector<ms::EmpLogData>database;
	public:
		Ministry(std::vector<ms::EmpLogData>base) {
			database = base;
		}
		std::vector<ms::EmpLogData>getDataBase(){
			return database;
		}
		void downloadDataBase() {															//method to download the data from database
			std::ifstream data;
			data.open("database.txt");
			if (data.is_open()) {
				std::vector<std::string>dataVec;
				std::vector<std::vector<std::string>>employees;
				std::string temp;
				while (std::getline(data, temp)) 											//temporarily filling vector with employee's data as string
					dataVec.push_back(temp);
				for (int i = 0; i < dataVec.size(); i++) {
					std::vector<std::string>employee;
					std::string part;
					std::istringstream iss(dataVec[i]);
					while (std::getline(iss, part, ' '))									//splitting long string with employee's data into
						employee.push_back(part);											//separate parts (isAdmin, ID, name, surname, password) and
					employees.push_back(employee);											//temporarily filling the vector with it
				}
				for (int i = 0; i < employees.size(); i++) {
					std::vector <std::string>temp;											
					temp = employees[i];													
					int isAdmin = std::stoi(temp[0]);
					int hoursAmount = std::stoi(temp[5]);
					char paymentApproval = (temp[6])[0];
					database.push_back(ms::EmpLogData(isAdmin, temp[1], temp[2], temp[3], temp[4], hoursAmount, paymentApproval));	//pushing EmpLogData object into database vector
				}
				data.close();
			}
			else
				throw "Couldn't find the database file!";
		}	
		ms::EmpLogData checkWho(std::string id, std::string password) {		//method to check if entered data fits to any employee
			ms::EmpLogData employee(0, "", "", "", "",0,'0');						//in the database
			for (auto i : database)
				if (id == i.getId() && password == i.getPassword()) {		//if entered data fits one of the employees it returns 
					employee = i;											//the valid, filled object, otherwise it retrurns 
					break;													//empty object which is then recognized in the main function
				}
			return employee;
		}
		std::vector<std::string>getIdVector() {								//method that returns vector filled with all available ids in database
			std::vector<std::string>idVector;
			for (auto i : database)
				idVector.push_back(i.getId());
			return idVector;
		}
		void rewriteDataBase() {
			std::ofstream ofs("database.txt", std::ofstream::trunc);									//opens the database and erases it's contents
			for (int i = 0; i < database.size(); i++) {													//iterates through all employees in database
				std::string newEmployeeStr, isAdminStr,hoursAmountStr,paymentApprovalStr;
				ms::EmpLogData temp = database[i];							
				isAdminStr = std::to_string(temp.IsAdmin());											//converts isAdmin from int to string
				hoursAmountStr = std::to_string(temp.getHoursAmount());									//converts hoursAmount from int to string
				paymentApprovalStr.push_back(temp.getPaymentApproval());								//converts char paymentApproval to string
				newEmployeeStr = isAdminStr + " " + temp.getId() + " " + temp.getName() +
					" " + temp.getSurname() + " " + temp.getPassword() + " " + hoursAmountStr + 
					" " + paymentApprovalStr + "\n";			
				ofs << newEmployeeStr;																	//writes employee to the database
			}
			ofs.close();
		}
		int findIndex(std::string id) {
			int n;
			for (int i = 0; i < database.size(); i++) {
				if (database[i].getId() == id) {
					n = i;
					break;
				}
			}
			return n;
		}
		// METHODS FOR ADMIN ONLY COMMANDS
		void hireEmployee(std::string id,std::string name,std::string surname,std::string password) {
			ms::EmpLogData newEmployee(0, id, name, surname, password,0,'0');
			database.push_back(newEmployee);
			rewriteDataBase();
		}
		void fireEmployee(std::string id) {
			int n = findIndex(id);
			database.erase(database.begin() + n);
			rewriteDataBase();
		}
		void promoteEmployee(std::string id) {
			int n = findIndex(id);
			if (database[n].IsAdmin() == 0) {
				database[n].setIsAdmin(1);
				database[n].setPaymentApproval('-');
				rewriteDataBase();
			}
			else
				throw "You can't prmote an admin!";
		}
		void demoteEmployee(std::string id) {
			int n = findIndex(id);			
			if (database[n].IsAdmin() == 1) {
				database[n].setIsAdmin(0);
				database[n].setPaymentApproval('0');
				rewriteDataBase();
			}
			else
				throw "You can't demote regular employee!";
		}
		void approvePayment(std::string id) {
			int n = findIndex(id);
			if (database[n].getPaymentApproval() == '1') {
				database[n].setPaymentApproval('0');
				database[n].setHoursAmount(0);
				rewriteDataBase();
			}
			else if (database[n].getPaymentApproval() == '0')
				throw "There is nothing to approve.";
			else if (database[n].getPaymentApproval() == '-')
				throw "Admins don't need payment approvals.";
		}
		// METHODS FOR EVERYBODY'S COMMANDS
		void changePassword(std::string newPassword, std::string id) {
			int n = findIndex(id);
			database[n].setPassword(newPassword);
			rewriteDataBase();
		}
		void addHours(double hours, std::string id) {
			int n = findIndex(id);
			double  hoursWorked = database[n].getHoursAmount();
			hoursWorked = hoursWorked + hours;
			database[n].setHoursAmount(hoursWorked);
			rewriteDataBase();
		}
		double seeHours(std::string id) {
			int n = findIndex(id);
			return database[n].getHoursAmount();
		}
		double getPaid(std::string id) {
			int n = findIndex(id);
			double hoursWorked = database[n].getHoursAmount();
			if (database[n].IsAdmin() == 1) {
				database[n].setHoursAmount(0);
				rewriteDataBase();
				return hoursWorked * 20.84;
			}
			else if (database[n].IsAdmin() == 0) 
				return hoursWorked * 10.42;
		}
		// METHODS FOR EMPLOYEE ONLY COMMANDS
		void waitForApproval(std::string id) {
			int n = findIndex(id);
			database[n].setPaymentApproval('1');
			rewriteDataBase();
		}
	};
}