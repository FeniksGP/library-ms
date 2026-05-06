#include "./database.h"

Database::Database(std::string t_filename): filename{t_filename}
{
  connect();
  searchId();
}

Database::~Database()
{
	file.close();
}

void Database::connect()
{
	file.open(filename, std::ios::out | std::ios::app | std::ios::in);
	if(!file.is_open())
	{
		throw ERR_OPEN;
	}
}

void Database::searchId()
{
  std::string buffer1;
  std::string buffer2;//zawiera ostania linijke

  file.seekg(0);//cofa wskaznik na poczatek
  while(getline(file, buffer1))
  {
    buffer2 = buffer1;
	++lines;
  }
  if(lines != 0)
  {
	  id = stoi(buffer2);
  }
  else
  {
	  id = 0;
  }
  file.clear();//usuwa bledy
}
