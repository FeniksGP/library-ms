#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <algorithm>

#include "./users.h"

Users::Users(std::string t_name, Library *t_lib): Database(t_name), mylib{t_lib}{}
Users::~Users(){}

int Users::add(std::string name, std::string surname)
{
  User user1(name, surname);
  User user2;
  if(search(user1, user2))
  {
	return 0;//istnieje
  }
  file << ++id << ";" << user1.toRaw() << std::endl;
  return 1;//nie istnieje
}

int Users::removeA(std::string name, std::string surname)
{
	User user1(name, surname);
	User user2;
	std::string buffer;
	std::string temp_name = "../lib/temp.txt";
	int line = search(user1, user2);
  
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

int Users::modify(std::string name, std::string surname, std::string c_name, std::string c_surname)
{
	return modify(name, surname, c_name, c_surname, "", false, false);
}

int Users::modify(std::string name, std::string surname, std::string c_name, std::string c_surname, std::string book, bool isAdd, bool isDel)
{//mamy boole ktore mowiam nam o tym czy dodajemy czy nie
	User user1(name, surname);
	User user2;
	std::string buffer;
	std::string temp_name = "../lib/temp.txt";
	int line = search(user1, user2);
  
	user2.set(*(user2.id), c_name, c_surname);
	
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
		if(isAdd)
		{
			temp << user2.raw() << book << ";" << std::endl;
		}
		else if(isDel)
		{
			delBook(user2.books, book);
			temp << user2.raw() << std::endl;
		}
		else
		{
			temp << user2.raw() << std::endl;
		}
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

unsigned int Users::search(User &pattern, User &result)
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

void Users::list()
{
	User a;
	std::string buffer;

	file.seekg(0);

	std::cout << "|     ID     |         Imie         |        Nazwisko       |             Wypozyczone ksiazki            |" << std::endl;
	std::cout << "----------------------------------------------------------------------------------------------------------" << std::endl;
	while(getline(file, buffer))
	{
		a.set(buffer);
		std::cout << a << std::endl;
	}
	file.clear();
}

int Users::borrow(std::string name, std::string surname, std::string title, std::string author)
{
	User user1(name, surname);
	User user2;
	Book book1(title, author);
	Book book2;
	int line1;
	int line2;

	line1 = search(user1, user2);
	if(line1 == 0)
	{
		return NO_EXIST_U;//Tu nie ma uzytkwonika
	}
	line2 = mylib->search(book1, book2);//zobacz czy istnieje i czy dostepna
	if(line2 == 0)
	{
		return NO_EXIST_D;//Tu nie ma ksiazki
	}
	if(book2.number < 1)
	{
		return NO_AVAIL_D;//nie ma ksiazki
	}

	if(!mylib->modify(book2.title, book2.author, book2.number - 1, book2.title, book2.author))
	{
		return -1;
	}
	if(!modify(user2.name, user2.surname, user2.name, user2.surname, title, true, false))
	{
		return -1;
	}
	return SUCC_BORROW_U;
}

int Users::get(std::string name, std::string surname, std::string title, std::string author)
{
	User user1(name, surname);
	User user2;
	Book book1(title, author);
	Book book2;
	std::vector <std::string> b;
	std::string buffer;
	int line1;
	int line2;
	bool found = false;

	line1 = search(user1, user2);
	if(line1 == 0)
	{
		return NO_EXIST_U;//Tu nie ma uzytkwonika
	}
	line2 = mylib->search(book1, book2);//zobacz czy istnieje i czy dostepna
	if(line2 == 0)
	{
		return NO_EXIST_D;//Tu nie ma ksiazki
	}

//sprawdza czy user posiada ksiazke
	std::stringstream sbuffer(user2.books);
	while(getline(sbuffer, buffer, ';'))
	{
		if( buffer != "\n")
		{
			b.push_back(buffer);
		}
	}
	for(auto it = b.begin(); it != b.end(); ++it)
	{
		if(*it == title)
		{
			found = true;
			break;
		}
	}
	if(!found)
	{
		return NO_HAVE_U; // komunikatot dot brak ksiazki u user
	}

	if(!mylib->modify(book2.title, book2.author, book2.number + 1, book2.title, book2.author))
	{
		return -1;
	}
	if(!modify(user2.name, user2.surname, user2.name, user2.surname, book2.title, false, true))
	{
		return -1;
	}
	return SUCC_GET_U;//udalo sie
}

void Users::delBook(std::string &books, std::string book)
{
	std::vector <std::string> b;
	std::string buffer;
	std::stringstream sbuffer(books);
	
	while(getline(sbuffer, buffer, ';'))
	{
		if( buffer != "\n")
		{
			b.push_back(buffer);
		}
	}
	books = "";
	auto ite = std::find(b.begin(), b.end(), book);
	b.erase(ite);
	
	for(auto& elem : b)
	{
		books += elem + ';';
	}
}
