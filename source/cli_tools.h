#ifndef CLI_TOOLS_H
#define CLI_TOOLS_H

#include <string>

#include "./library_sys/library.h"
#include "./library_sys/users.h"

enum Actions
{
  ADD = 0,
  REMOVE,
  MODIFY,
  LIST,
  BORROW,
  GET,
  NOTHING
};

enum Kinds
{
	LIBRARY = 0,
	USER,
	UNDEFINED
};

struct Run
{
	Kinds kinds;
	Actions action;
	std::string data[5];
};

class Arguments;

class Commands
{
	public:
		Commands(Library *t_lib, Users *t_user);
		~Commands();
		
		void interact_mode();
		int execute();
	private:
		Run *run {NULL};
		Library *lib;
		Users *user;
		int (Commands::*operation[6])() {&Commands::add, &Commands::remove, &Commands::modify, &Commands::list, &Commands::borrow, &Commands::get};
		
		int add();
		int remove();
		int modify();
		int list();
		int borrow();
		int get();
		
	friend void copy(Commands &com, Arguments &arg);
};

class Arguments
{
	public:
		bool isWrongArg {false};
		bool isInter {false};
		bool isOneTime {false};

		Arguments(int t_argc, char *t_argv[]);
		Arguments();
		~Arguments();
  
		void parse();
		void parse(int t_argc, char *t_argv[]);
	private:
		int argc {0};
		char **argv;
		Run run {UNDEFINED, NOTHING, {}};
  
		void parsing();
		void helper();
		void version();
		
	friend void copy(Commands &com, Arguments &arg);
};

void copy(Commands &com, Arguments &arg);

#endif
