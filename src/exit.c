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

static void	exit_was_too_long(char **s_line, t_parsing **parse)
{
	int	i;

	if (s_line[1] == NULL)
	{
		printf("exit\n");
		rl_clear_history();
		ft_exit(*parse); // TODO Double check if OK
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
			ft_exit(*parse);// TODO Double check if OK
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
void	mini_exit(char **s_line, t_parsing *parse)
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
	exit_was_too_long(s_line, &parse);
	tmp = ft_atoi(s_line[1]);
	printf("exit\n");
	rl_clear_history();
	ft_exit(parse); // TODO Double check if OK
	exit (tmp);
}


void	ft_exit(t_parsing* parse)
{
	/* PARSING  */
	// free parse_list->tkn->list 
	// TODO maybe free tkn_list->vector_cmd here ?
	if (parse && parse->tkns_list)
	{
		t_tkns	*tmp;
		while(parse->tkns_list)
		{
			tmp = parse->tkns_list->next;
			for (int i = 0; parse->tkns_list->vector_cmd[i]; i++)
				free(parse->tkns_list->vector_cmd[i]);
			free(parse->tkns_list->vector_cmd);
			free(parse->tkns_list->data);
			free(parse->tkns_list);
			parse->tkns_list = tmp;
		}
		parse->tkns_list = NULL;
	}
	// free parse->vector->cmd
	if (parse && parse->vector_cmd)
	{
		for (int i = 0; parse->vector_cmd[i]; i++)
			free(parse->tkns_list->vector_cmd[i]);
	}
	//free parse->pids
	if (parse && parse->pids)
		free (parse->pids);
	// free parse->pipe_args
	if (parse && parse->pipes_args)
	{
		for (int i = 0;parse->pipes_args[i]; i++)
		{
			for (int j = 0; parse->pipes_args[i][j];j++)
			{
				free(parse->pipes_args[i][j]);
			}
		}
	}
	//free parse->p_new (expand variables)

	// free parse_list
	if (parse)
		free(parse);
	/* EXEC  */
	// free ex->line
	if (ex && ex->line)
		free(ex->line);
	// free ex->s_line
	if (ex && ex->s_line)
		free_strrarr(ex->s_line);
	// free env
	if (ex && ex->new_env)
		free_strrarr(ex->new_env);
	// free ex
	if (ex)
		free(ex);


}