#pragma once
#include<string>
#include<ostream>
namespace ms {
	class Employee {
		std::string name;
		std::string surname;
		double hoursAmount;
		char paymentApproval;
	public:
		Employee(const std::string& name,const std::string& surname,const double& hoursAmount, const char& paymentApproval) : 
			name(name), surname(surname), hoursAmount(hoursAmount), paymentApproval(paymentApproval){};

		std::string getName() const noexcept {
			return name;
		}
		std::string getSurname() const noexcept {
			return surname;
		}
		double getHoursAmount() const noexcept {
			return hoursAmount;
		}
		char getPaymentApproval() const noexcept {
			return paymentApproval;
		}
		void setHoursAmount(double newHours) {
			hoursAmount = newHours;
		}
		void setPaymentApproval(char newPaymentApproval) {
			paymentApproval = newPaymentApproval;
		}

	};
	std::ostream& operator << (std::ostream& out, const Employee& employee) {
		out << "Name: " << employee.getName() << std::endl;
		out << "Surname: " << employee.getSurname() << std::endl;
		return out;
	}
}