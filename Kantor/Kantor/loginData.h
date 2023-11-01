#pragma once
#include "User.h"
namespace ms {
	class loginData : public User {
		std::string id;
		std::string password;
	public:
		loginData(const int& isAdmin, const std::string& name, const std::string& surname, const ms::Account& balance, const std::string& id, const std::string& password)
			: ms::User(isAdmin, name, surname,balance), id(id), password(password) {};

		std::string getId() const noexcept {
			return id;
		}
		std::string getPassword() const noexcept {
			return password;
		}
		void setPassword(std::string newPassword) {
			password = newPassword;
		}
	};
	std::ostream& operator << (std::ostream& out, const loginData& logindata) {
		out << logindata.getIsAdmin() << std::endl;
		out << logindata.getName() << std::endl;
		out << logindata.getSurname() << std::endl;
		out << logindata.getBalance();
		out << logindata.getId() << std::endl;
		out << logindata.getPassword() << std::endl;
		return out;
	}
}
