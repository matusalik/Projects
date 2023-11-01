#pragma once
namespace ms {
	class Account {
		double zloty;
		double euro;
		double dolar;
	public:
		Account(const double& zloty, const double& euro, const double& dolar) :
			zloty(zloty), euro(euro), dolar(dolar) {};

		double getZloty() const noexcept {
			return zloty;
		}
		double getEuro() const noexcept {
			return euro;
		}
		double getDolar() const noexcept {
			return dolar;
		}
		void setZloty(double zl) {
			zloty = zl;
		}
		void setEuro(double eur) {
			euro = eur;
		}
		void setDolar(double dol) {
			dolar = dol;
		}
	};
	std::ostream& operator << (std::ostream& out, const Account& account) {
		out << "Zloty: " << account.getZloty() << std::endl;
		out << "Euro: " << account.getEuro() << std::endl;
		out << "Dolar: " << account.getDolar() << std::endl;
		return out;
	}
}
