#ifndef DATA_H
#define DATA_H

#include <string>


#define ERR_OPEN 0
#define ERR_WRITE 1
#define ERR_FILE 2

#define VERSION_D 0
#define HELP_D 1
#define WR_ARG_D 2
#define SUCC_ADD_D 3
#define EXIST_D 4
#define SUCC_DEL_D 5
#define NO_EXIST_D 6
#define SUCC_MOD_D 7
#define SUCC_ADD_U 8
#define EXIST_U 9
#define SUCC_DEL_U 10
#define NO_EXIST_U 11
#define SUCC_MOD_U 12
#define NO_AVAIL_D 13
#define NO_HAVE_U 14
#define SUCC_GET_U 15
#define SUCC_BORROW_U 16

extern const std::string text[];
extern const std::string errors[];
#endif
