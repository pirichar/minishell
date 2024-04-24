#include "../include/minishell.h"

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
