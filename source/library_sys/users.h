#ifndef USERS_H
#define USERS_H

#include <fstream>
#include <string>

#include "./database.h"
#include "./library.h"
#include "../entity/user.h"
#include "../entity/book.h"
#include "../data.h"

class Users: public Database
{
	private:
		Library *mylib;
	
	public:
		Users(std::string t_name , Library *t_lib);
		Users(Users &t) = delete;
		~Users();
		
		int add(std::string name, std::string surname);
		int removeA(std::string name, std::string surname);
		int modify(std::string name, std::string surname, std::string c_name, std::string c_surname);
		int modify(std::string name, std::string surname, std::string c_name, std::string c_surname, std::string book, bool isAdd, bool isDel);
		unsigned int search(User &pattern, User &result);
		void list();
		int borrow(std::string name, std::string surname, std::string title, std::string author);
		int get(std::string name, std::string surname, std::string title, std::string author);
		void delBook(std::string &books, std::string book);
};

#endif