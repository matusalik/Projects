#include <iostream>


namespace ms {
	class loggedCommand {
	public:
		virtual void execute() = 0;
	};

	class helpCommand : public loggedCommand {
	public:
		virtual void execute() {
			std::cout << "'logout' - logs you out of your account." << std::endl;
			std::cout << "'changepassword - changes your password." << std::endl;
		}
	};

	class changepasswordCommand : public loggedCommand {
		ms::userBase users;
		int UI;		//user indicator
		std::string newPassword;
	public:
		changepasswordCommand(const ms::userBase& sentUsers,const int& sentUI,std::string& sentNewPassword) {
			users = sentUsers;
			UI = sentUI;
			newPassword = sentNewPassword;
		}
		virtual void execute() {
			std::vector<ms::loginData> base = users.getUsers();
			base[UI].setPassword(newPassword);
			users.rewriteDataBase(base);
		}
	};
}