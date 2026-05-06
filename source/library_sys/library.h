#ifndef LIBRARY_H
#define LIBRARY_H

#include <fstream>
#include <string>

#include "../data.h"
#include "../entity/book.h"
#include "./database.h"

class Library: public Database
{
	public:
		Library(std::string t_library_name);
		~Library();
		Library(Library &t) = delete;
  
		int add(std::string title, std::string autor, unsigned int number);
		int removeA(std::string title, std::string author);
		int modify(std::string title, std::string author, unsigned int c_number, std::string c_title, std::string c_author);
		unsigned int search(Book &pattern, Book &result);
		void list();
		
	friend class Users;
};

#endif
