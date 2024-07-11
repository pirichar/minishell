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
		printf("exit	if (s_line[1] == NULL) \n");
		rl_clear_history();
		ft_exit(*parse);
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
			ft_exit(*parse);
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
	printf("exit within mini exit\n");
	rl_clear_history();
	ft_exit(parse);
	exit (tmp);
}

/**
 * @brief Function called at the end of each cycle of minishell
	
* 	PARSING STRUCT
	// free parse_list->tkn->list 
	// free parse->vector->cmd and s_line 
	// free parse->pipe_args
	//free parse->p_new (expand variables)
	// free parse_list

	EXEC
	// free g_ex.line

	Pids are freed in wait for pids
 * 
 * @param parse struct to free
 */
void	ft_clean(t_parsing	**parse)
{
	t_tkns	*tmp;

	if ((*parse) && (*parse)->tkns_list)
	{
		while ((*parse)->tkns_list)
		{
			tmp = (*parse)->tkns_list->next;
			free((*parse)->tkns_list->data);
			free((*parse)->tkns_list);
			(*parse)->tkns_list = tmp;
		}
	}
	if ((*parse) && *(*parse)->vector_cmd)
		free_strrarr((*parse)->vector_cmd);
	if ((*parse) && (*parse)->pipes_args)
	{
		(*parse)->i = 0;
		while ((*parse)->pipes_args[(*parse)->i])
			free_strrarr((*parse)->pipes_args[(*parse)->i++]);
	}
	free ((*parse)->pipes_args);
	free ((*parse)->p_new);
	free ((*parse));
	*parse = NULL;
	free (g_ex.line);
}

/**
 * @brief Function called when the program is closing
	
* 	PARSING STRUCT
	// free parse_list->tkn->list 

	EXEC
	// free g_ex.line
	// free env
	// free ex

 * 
 * @param parse struct to free
 */
void	ft_exit(t_parsing	*parse)
{
	t_tkns	*tmp;

	if (parse && parse->tkns_list)
	{
		while (parse->tkns_list)
		{
			tmp = parse->tkns_list->next;
			free(parse->tkns_list->data);
			free(parse->tkns_list);
			parse->tkns_list = tmp;
		}
	}
	free (g_ex.line);
	if (g_ex.fail_heredoc == false)
		free_strrarr(g_ex.new_env);
}
