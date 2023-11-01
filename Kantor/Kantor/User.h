#pragma once
#include "Account.h"
#include <string>
namespace ms {
	class User {
		int isAdmin;
		std::string name;
		std::string surname;
		ms::Account balance;
	public:
		User(const int& isAdmin, const std::string& name, const std::string& surname, const ms::Account& balance) :
			isAdmin(isAdmin), name(name), surname(surname), balance(balance) {};

		int getIsAdmin() const noexcept {
			return isAdmin;
		}
		std::string getName() const noexcept {
			return name;
		}
		std::string getSurname() const noexcept {
			return surname;
		}
		ms::Account getBalance() const noexcept {
			return balance;
		}
	};
}
