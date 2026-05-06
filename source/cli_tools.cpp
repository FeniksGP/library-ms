#include <iostream>

#include "cli_tools.h"
#include "data.h"

Arguments::Arguments(int t_argc, char *t_argv[]): argc{t_argc}, argv{t_argv}
{
	parse();
}

Arguments::Arguments(){}
Arguments::~Arguments(){}

void Arguments::parse()
{
	std::string arg;

	if(argc < 2)
	{
	//interaktywny interfejs (zobacz potem)
		isInter = true;
		return;
	}
	arg = argv[1];

	if(arg[0] == '-')
	{
		if(arg[1] == '-')
		{
			if(arg == "--help")
			{
				helper();
				isOneTime = true;
			}
			else if(arg == "--version")
			{
				version();
				isOneTime = true;
			}
			else
			{
				//zly argrgument
				isWrongArg = true;
			}
		}
		else
		{
			if(arg[1] == 'h')
			{
				helper();
				isOneTime = true;
			}
			else if(arg[1] == 'v')
			{
				version();
				isOneTime = true;
			}
			else
			{
				//zly argrgument
				isWrongArg = true;
			}
		}
    }
	else
	{
		parsing();
	}
}

void Arguments::parse(int t_argc, char *t_argv[])//chyba ok
{
	argc = t_argc;
	argv = t_argv;
	parse();
}

void Arguments::parsing()
{
	std::string arg;

	if(argc < 3)
	{
		isWrongArg = true;
		return;
	}
	arg = argv[2];
	
	if(arg == "book")
	{
		run.kinds = LIBRARY;
		arg = argv[1];
	
		if(arg == "list")
		{
			run.action = LIST;
		}
		else if(argc == 5)
		{
			if(arg == "remove")
			{
				run.action = REMOVE;
			}
			else
			{
				isWrongArg = true;
				return;
			}
			run.data[0] = argv[3];
			run.data[1] = argv[4];
		}
		else if(argc == 6)
		{
			if(arg == "add")
			{
				run.action = ADD;
			}
			else
			{
			isWrongArg = true;
				return;
			}
			run.data[0] = argv[3];
			run.data[1] = argv[4];
			run.data[2] = argv[5];
		}
		else if(argc == 8)
		{
			if(arg == "modify")
			{
				run.action = MODIFY;
			}
			else
			{
				isWrongArg = true;
				return;
			}
			run.data[0] = argv[3];
			run.data[1] = argv[4];
			run.data[2] = argv[5];
			run.data[3] = argv[6];
			run.data[4] = argv[7];
		}
		else
		{
			isWrongArg = true;
		}
	}
	else if(arg == "user")
	{
		run.kinds = USER;
		arg = argv[1];
	
		if(arg == "list")
		{
			run.action = LIST;
		}
		else if(argc == 5)
		{
			if(arg == "remove")
			{
				run.action = REMOVE;
			}
			else if(arg == "add")
			{
				run.action = ADD;
			}
			else
			{
				isWrongArg = true;
				return;
			}
			run.data[0] = argv[3];
			run.data[1] = argv[4];
		}
		else if(argc == 7)
		{
			if(arg == "modify")
			{
				run.action = MODIFY;
			}
			else if(arg == "borrow")
			{
				run.action = BORROW;
			}
			else if(arg == "get")
			{
				run.action = GET;
			}
			else
			{
				isWrongArg = true;
				return;
			}
			run.data[0] = argv[3];
			run.data[1] = argv[4];
			run.data[2] = argv[5];
			run.data[3] = argv[6];
		}
		else
		{
			isWrongArg = true;
		}
	}
	else
	{
		isWrongArg = true;
		return;
	}
}

void Arguments::helper()
{
  std::cout << text[HELP_D] << std::endl;
}

void Arguments::version()
{
  std::cout << text[VERSION_D]  << std::endl;
}

Commands::Commands(Library *t_lib, Users *t_user): lib{t_lib}, user{t_user}{}
Commands::~Commands(){}

int Commands::execute()
{
	return (*this.*(operation[run->action]))();
}

int Commands::add()
{
	if(run->kinds == LIBRARY)
	{
		if(lib->add(run->data[0], run->data[1], stoi(run->data[2])))
		{
			return SUCC_ADD_D;
		}
		return EXIST_D;
	}
	else if(run->kinds == USER)
	{
		if(user->add(run->data[0], run->data[1]))
		{
			return SUCC_ADD_U;
		}
		return EXIST_U;
	}
	return -1;
}

int Commands::remove()
{
	if(run->kinds == LIBRARY)
	{
		if(lib->removeA(run->data[0], run->data[1]))
		{
			return SUCC_DEL_D;
		}
		return NO_EXIST_D;
	}
	else if(run->kinds == USER)
	{
		if(user->removeA(run->data[0], run->data[1]))
		{
			return SUCC_DEL_U;
		}
		return NO_EXIST_U;
	}
	return -1;
}
int Commands::modify()
{	
	if(run->kinds == LIBRARY)
	{
		if(lib->modify(run->data[0], run->data[1], stoi(run->data[2]), run->data[3], run->data[4]))
		{
			return SUCC_MOD_D;
		}
		return NO_EXIST_D;
	}
	else if(run->kinds == USER)
	{
		if(user->modify(run->data[0], run->data[1], run->data[2], run->data[3]))
		{
			return SUCC_MOD_U;
		}
		return NO_EXIST_U;
	}
	
	return -1;
}
int Commands::list()
{
	if(run->kinds == LIBRARY)
	{
		lib->list();
	}
	else if(run->kinds == USER)
	{
		user->list();
	}
	return -1;
}

int Commands::borrow()
{
	return user->borrow(run->data[0], run->data[1], run->data[2], run->data[3]);
}

int Commands::get()
{
	return user->get(run->data[0], run->data[1], run->data[2], run->data[3]);
}

void Commands::interact_mode(){}

void copy(Commands &com, Arguments &arg)
{
	com.run = &arg.run;
}

