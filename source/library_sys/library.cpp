#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

#include "./library.h"

Library::Library(std::string t_filename): Database(t_filename){}
Library::~Library(){}

int Library::add(std::string title, std::string author, unsigned int number)
{
  std::vector <Entity *> enti;
  Book book1(title, author);
  Book book2(book1);

  enti.push_back(new Numb(++id));
  enti.push_back(new Text(";"));
  enti.push_back(new Book(title, author));
  enti.push_back(new Numb(number));
  enti.push_back(new Text(";"));
  enti.push_back(new Text("\n"));

  if(search(book1, book2))
  {
	for(auto& elem : enti)
	{
		delete elem;
	}
	return 0;//istnieje
  }
  //file << ++id << enti[1]->toRaw() << enti[0]->toRaw() << number << enti[0]->toRaw() << std::endl;

  for(auto& elem : enti)
  {
    file << elem->toRaw();
  }

  for(auto& elem : enti)
  {
    delete elem;
  }
  return 1;//nie istnieje
}

int Library::removeA(std::string title, std::string author)
{
	Book book1(title, author);
	Book book2;
	std::string buffer;
	std::string temp_name = "../lib/temp.txt";
	int line = search(book1, book2);
  
	if(line)
	{
		std::fstream temp;
		temp.open(temp_name, std::ios::out);
		if(!temp.is_open())
		{
			throw ERR_WRITE;
		}
		file.seekg(0);

		for(int i = 0; i < line - 1; ++i)
		{
			getline(file, buffer);
			temp << buffer << std::endl;
		}
		getline(file, buffer);
		while(getline(file, buffer))
		{
			temp << buffer << std::endl;
		}

		file.clear();
		temp.close();
		file.close();

		if(remove(filename.c_str()))
		{
			throw ERR_FILE;
		}

		if(rename(temp_name.c_str(), filename.c_str()) != 0)
		{
			throw ERR_FILE;
		}

		connect();

		return 1;//juz istnieje
	}
	return 0;
}

int Library::modify(std::string title, std::string author, unsigned int c_number, std::string c_title, std::string c_author)
{
	Book book1(title, author);
	Book book2;
	std::string buffer;
	std::string temp_name = "../lib/temp.txt";
	int line = search(book1, book2);
  
	book2.set(*(book2.id), c_title, c_author, c_number);
	
	if(line)
	{
		std::fstream temp;
		temp.open(temp_name, std::ios::out);

		if(!temp.is_open())
		{
			throw ERR_WRITE;
		}
		file.seekg(0);

		for(int i = 0; i < line-1; ++i)
		{
			getline(file, buffer);
			temp << buffer << std::endl;
		}
		getline(file, buffer);
		temp << book2.raw() << std::endl;
		while(getline(file, buffer))
		{
			temp << buffer << std::endl;
		}

		file.clear();
		temp.close();
		file.close();

		if(remove(filename.c_str()))
		{
			throw ERR_FILE;
		}

		if(rename(temp_name.c_str(), filename.c_str()) != 0)
		{
			throw ERR_FILE;
		}

		connect();

		return 1;//juz istnieje
	}
  return 0;//nie istnieje
}

unsigned int Library::search(Book &pattern, Book &result)
{
  std::string buffer;
  unsigned int line_number = 0;
  
  file.seekg(0);

  while(getline(file, buffer))
  {
	++line_number;
	result.set(buffer);
	if(pattern == result)
	{
		file.clear();
		return line_number;//nr wiersza
	}
	
  }

  file.clear();
  return 0;//nie znalazl
}

void Library::list()
{
	Book a;
	std::string buffer;

	file.seekg(0);

	std::cout << "|     ID     |         Tytul        |         Autor        |    Ilosc   |" << std::endl;
	std::cout << "-------------------------------------------------------------------------" << std::endl;
	while(getline(file, buffer))
	{
		a.set(buffer);
		std::cout << a << std::endl;
	}
	file.clear();
}
