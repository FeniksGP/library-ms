#include <sstream>
#include <iomanip>

#include "user.h"

User::User(){}
User::~User(){}

User::User(std::string t_name, std::string t_surname): name{t_name}, surname{t_surname}{}

std::string User::toRaw()
{
  return name + ";" + surname + ";";
}

std::string User::raw()
{
	std::stringstream buffer1;
	std::string buffer2;
	buffer1 << *id << ";" << name << ";" << surname << ";" << books;
	buffer1 >> buffer2;
	return buffer2;
}

void User::set(unsigned int t_id, std::string t_name, std::string t_surname)
{
	*id = t_id;
	name = t_name;
	surname = t_surname;
}

void User::set(std::string raw)
{
	std::string buffer;
	std::stringstream sbuffer(raw);
	
	getline(sbuffer, buffer, ';');//tutaj odczyt id
	*id = stoi(buffer);
    getline(sbuffer, buffer, ';');//tutaj odczyt name
	name = buffer;
    getline(sbuffer, buffer, ';');//tutaj odczyt surname
	surname = buffer;
	getline(sbuffer, buffer);//ksiazki
	books = buffer;
}

bool User::operator==(User &user)
{
	if(name == user.name && surname == user.surname)
	{
		return true;
	}
	return false;
}

std::ostream& operator<<(std::ostream &out, const User &user)
{
	out << "| " << std::setw(10) << *(user.id) << " | " << std::setw(20)  << user.name << " | " << std::setw(21) << user.surname << " |" << std::setw(43) << user.books << " |";
	return out;
}
