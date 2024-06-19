#include "../include/minishell.h"

/**
 * @brief The end of exit,
			makes sure that exit acts like bash's exit
			with exit or with a non numeric arg
 * 
// TO-DO MAKE SURE THIS IS FINE :
	[I should free :
		the new_env,
		all the parsing structure, 
		la structure EX, 
		la LINE 
		closer mes FD]

 * @param s_line command line splitted
 */

static void	exit_was_too_long(char **s_line)
{
	int	i;

	if (s_line[1] == NULL)
	{
		printf("exit\n");
		rl_clear_history();
		exit (0);
	}
	i = 0;
	while (s_line[1][i])
	{
		if (s_line[1][i] < '0' || s_line[1][i] > '9')
		{
			printf("exit\n");
			printf("Dundershell: exit: %s: numeric argument required\n",
				s_line[1]);
			rl_clear_history();
			exit (255);
		}
		i++;
	}
}

/**
 * @brief Builtin function
			Basically exit function
			will not exit with more then one argument

// TO-DO VÉRIFIER ÇA 
	étrangement quand je free line et s_line j'ai un leak mais 
	le leak part quand je ne les free pas ; je devrais vérifier pourquoi bientôt
 * 
 * @param s_line splitted line 
 * @param parse for the builtin
 */
void	mini_exit( char **s_line, t_parsing *parse)
{
	int	tmp;
	int	i;

	i = 1;
	parse->b_in = true;
	while (s_line[i++])
		;
	if (i > 3)
	{
		printf("Dundershell: exit: too many arguments\n");
		return ;
	}
	exit_was_too_long(s_line);
	tmp = ft_atoi(s_line[1]);
	printf("exit\n");
	rl_clear_history();
	exit (tmp);
}
