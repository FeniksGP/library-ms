#ifndef BOOK_H
#define BOOK_H

#include <string>

#include "entity.h"

class Book: public Entity
{
	private:
		std::string title;
		std::string author;
		unsigned int number {0};
		
	public:
		Book();
		Book(std::string t_title, std::string t_author);
		Book(const Book &other);
		~Book();
	
		std::string toRaw()  override;
		std::string raw() override;
		void set(unsigned int t_id, std::string t_title, std::string t_author, unsigned int t_number);
		void set(std::string raw) override;
		bool operator==(Book &book);
	
	friend std::ostream& operator<<(std::ostream &out, const Book &book);
	friend class Users;
};


class Text: public Entity
{
        private:
                std::string text {""};
        public:
                Text(std::string t_text);
                ~Text();
        
                std::string toRaw()  override;
                std::string raw() override;
                void set(std::string raw) override;
};

class Numb: public Entity
{
        private:
                std::string number {""};
        public:
               	Numb(int t_number);
                ~Numb();
        
                std::string toRaw()  override;
                std::string raw() override;
                void set(std::string raw) override;
};

#endif
