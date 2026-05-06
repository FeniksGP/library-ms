#ifndef DATABASE_H
#define DATABASE_H

#include <fstream>
#include <string>

#include "../data.h"

class Database
{
	public:
		Database(std::string t_filename);
		~Database();
		Database(Database &t) = delete;
	protected:
		unsigned int id;
		unsigned int lines {0};
		std::string filename;
		std::fstream file;

		void searchId();
		void connect();
};

#endif