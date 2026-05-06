#include <iostream>

#include "./cli_tools.h"
#include "./library_sys.h"
#include "./data.h"

template <typename T>
void print_com(T a)
{
	std::cout << text[a] << std::endl;
}

int main(int argc, char *argv[])
{
	Arguments cli_args;
	cli_args.parse(argc, argv);
  
	if(cli_args.isWrongArg)
	{
		print_com(WR_ARG_D);
		return 0;
	}
	if(cli_args.isOneTime)
	{
		return 0;
	}

	try
	{
		Library library = {"../lib/library.txt"};
		Users users = {"../lib/users.txt", &library};
		Commands command = {&library, &users};
		
		/*if(cli_args.isInter)
		{
			command.interact_mode();
		}
		else
		{*/
			int status;
			copy(command, cli_args);
			if((status = command.execute()) != -1)
			{
				print_com(status);
			}
		//}
	}
	catch(int error_code)
	{ 
		std::cerr << errors[error_code] << std::endl;
		return 1;
	}
	return 0;
}
