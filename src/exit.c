/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adube <adube@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:43:51 by pirichar          #+#    #+#             */
/*   Updated: 2024/08/19 14:32:06 by adube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	null_exit(t_parsing **parse)
{
	printf("exit\n");
	rl_clear_history();
	ft_exit(*parse);
	exit (0);
}

static void	exit_was_too_long(char **s_line, t_parsing **parse)
{
	int	i;

	if (s_line[1] == NULL)
		null_exit(parse);
	i = 0;
	while (s_line[1][i])
	{
		if (s_line[1][i] < '0' || s_line[1][i] > '9')
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			ft_putstr_fd("Dundershell: exit: ", STDERR_FILENO);
			ft_putstr_fd(s_line[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
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
void	mini_exit(char **s_line, t_parsing *parse, bool local)
{
	int	tmp;

	parse->i = 1;
	parse->b_in = true;
	parse->bin_do_not_wait = true;
	while (s_line[parse->i++])
		;
	if (parse->i > 3)
	{
		ft_putstr_fd("Dundershell: exit: too many arguments\n", STDERR_FILENO);
		if (local)
		{
			g_ex.status = 1;
			return ;
		}
		else
			clean_and_exit(1);
	}
	exit_was_too_long(s_line, &parse);
	tmp = ft_atoi(s_line[1]);
	printf("exit\n");
	rl_clear_history();
	ft_exit(parse);
	exit (tmp);
}
