#ifndef USER_H
#define USER_H

#include <string>

#include "entity.h"

class User: public Entity
{
	private:
		std::string name;
		std::string surname;
		std::string books {""};
	public:
		User();
		User(std::string t_name, std::string t_surname);
		~User();

		std::string toRaw() override;
		std::string raw() override;
		void set(std::string raw) override;
		void set(unsigned int t_id, std::string t_name, std::string t_surname);
		bool operator==(User &user);
		
	friend std::ostream& operator<<(std::ostream &out, const User &user);
	friend class Users;
};

#endif
