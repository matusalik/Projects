#pragma once
#include"Employee.h"
namespace ms {
	class EmpLogData : public Employee {
		int isAdmin;
		std::string ID;
		std::string password;
	public:
		EmpLogData(const int& isAdmin, const std::string& ID, const std::string& name, const std::string& surname,const std::string& password,const double& hoursAmount, const char& paymentApproval) : 
			ms::Employee(name, surname, hoursAmount, paymentApproval), isAdmin(isAdmin) , ID(ID) , password(password) {}

		int IsAdmin() const noexcept {
			return isAdmin;
		}

		std::string getId() const noexcept {
			return ID;
		}

		std::string getPassword() const noexcept {
			return password;
		}	

		void setIsAdmin(int newIsAdmin) {
			isAdmin = newIsAdmin;
		}

		void setPassword(std::string newPassword) {
			password = newPassword;
		}

	};
	std::ostream& operator << (std::ostream& out, const EmpLogData& emplogdata) {
		if (emplogdata.IsAdmin() == 1)
			out << "ADMIN" << std::endl;
		out << "ID: " << emplogdata.getId() << std::endl;
		out << "Name: " << emplogdata.getName() << std::endl;
		out << "Surname: " << emplogdata.getSurname() << std::endl;
		out << "Password: " << emplogdata.getPassword() << std::endl;
		return out;
	}
}
