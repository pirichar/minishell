#include "../include/minishell.h"

/**
* @brief Builtin function
		Our version of PWD
		Using getCWD to get it
 * 
 * @param parse to set b_in true
 */
void	mini_pwd(t_parsing *parse)
{
	char	*to_print;
	char	*buff;

	parse->b_in = true;
	buff = NULL;
	to_print = getcwd(buff, 1024);
	printf("%s\n", to_print);
	free(to_print);
	free(buff);
}
