#include "book.h"
#include <sstream>
#include <iomanip>

Book::Book(){}
Book::Book(std::string t_title, std::string t_author): title{t_title}, author{t_author}{}
Book::~Book(){}

Book::Book(const Book &other): Entity(),  title{other.title}, author{other.author}
{
	delete id;//nie powinno byc potrzebne bo entity zrobi za nas
	id = new unsigned int;
	*id = 0;
}

std::string Book::toRaw()
{
  return title + ";" + author + ";";
}

std::string Book::raw()
{
	std::stringstream buffer1;
	std::string buffer2;
	buffer1 << *id << ";" << title << ";" << author << ";" << number << ";";
	buffer1 >> buffer2;
	return buffer2;
}

void Book::set(unsigned int t_id, std::string t_title, std::string t_author, unsigned int t_number)
{
	*id = t_id;
	title = t_title;
	author = t_author;
	number = t_number;
}

void Book::set(std::string raw)
{
	std::string buffer;
	std::stringstream sbuffer(raw);
	
	getline(sbuffer, buffer, ';');//tutaj odczyt id
	*id = stoi(buffer);
    getline(sbuffer, buffer, ';');//tutaj odczyt tytul
	title = buffer;
    getline(sbuffer, buffer, ';');//tutaj odczyt autor
	author = buffer;
	getline(sbuffer, buffer, ';');//tutaj odczyt ilosc
	number = stoi(buffer);
}

bool Book::operator==(Book &book)
{
	if(title == book.title && author == book.author)
	{
		return true;
	}
	return false;
}

std::ostream& operator<<(std::ostream &out, const Book &book)
{
	out << "| " << std::setw(10) << *(book.id) << " | " << std::setw(20)  << book.title << " | " << std::setw(20) << book.author << " | " << std::setw(10) << book.number << " |";
	return out;
}


Text::Text(std::string t_text): text{t_text}{}
Text::~Text(){}

std::string Text::toRaw()
{
	return text;
}

std::string Text::raw()
{
	return text;
}

void Text::set(std::string raw)
{
	text = raw;
}

Numb::Numb(int t_number)
{
	number = std::to_string(t_number);
}
Numb::~Numb(){}

std::string Numb::toRaw()
{
        return number;
}

std::string Numb::raw()
{
        return number;
}

void Numb::set(std::string raw)
{
        number = raw;
}
