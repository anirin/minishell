#ifndef MAIN_H
#define MAIN_H

#define FIND_SPACE 0 //space
#define FIND_SINGL_QUOTE 1 //'
#define FIND_DOUBLE_QUOTE 2 //"
#define FIND_PARETHESES 3 //(
#define FIND_CURLY_BRACKETS 4 //{

//readline
#include <readline/readline.h>
#include <readline/history.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <libc.h>

#include "libft.h"

//lexer
t_list *lexer(char *line);
void print_list(t_list *list);

#endif