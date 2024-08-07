/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adube <adube@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:43:32 by pirichar          #+#    #+#             */
/*   Updated: 2024/08/01 12:49:58 by adube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Static function used take care of -nnnnnnnnn
 * 
 * @param str to check
 * @return true if every character of the strings are a min n
 * @return false if there is anything else then n
 */
// TO-DO s'assurer que dans la version officielle echo "-n" 
// fonctionne aussi mais pas echo " -n" (comme dans bash)
static bool	check_only_n(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief This function takes care of the multiples by mooving the pointer
			over each elements of the array while its -n
 * 
 * @param s_line array of strings to check
 * @param check_nl bool that makes sure we have to check the nl in the while loop
 * @param with_nl return false if only_n return true
 * @param i index passed by mini_echo 
 */
static void	parse_echo(char **s_line, bool *check_nl, bool *with_nl, int *i)
{
	while (s_line[*(i)] && ft_strncmp(s_line[*(i)], "-n", 2) == 0
		&& (*check_nl))
	{
		if (check_only_n(s_line[*(i)]))
			(*with_nl) = false;
		else
			break ;
		(*i)++;
	}
}

void	set_parse_bools(t_parsing *parse)
{
	parse->with_nl = true;
	parse->check_nl = true;
	parse->b_in = true;
	parse->bin_do_not_wait = true;
}

/**
 * @brief maybe add back //close(p->outfile)

 * 
 * @param p 
 */
static void	exit_echo_child(t_parsing *p)
{
	(void)p;
	close(p->outfile);
	clean_and_exit(g_ex.status);
}

/**
 * @brief This function basically printf stuff
			It first look for -n -nnn and multiples -n
			Then once it filtered all the -n
			After that it set check_nl to false
			this way it does not look for flags
			to parse but print them out instead
			So our echo act more like zsh then bash its a decision we made
			Because of -n -n -n working 
			we now also check that the outfile is not -1
 * @param s_line line to print
 * @param parse used to check the NEW LINE and to set the b_in is true
 */
void	mini_echo(char **s_line, t_parsing *p, bool local)
{
	p->i = 1;
	set_parse_bools(p);
	if (p->outfile != -1)
	{
		while (s_line[p->i])
		{
			parse_echo(s_line, &p->check_nl, &p->with_nl, &p->i);
			if (s_line[p->i] == NULL)
				return ;
			p->check_nl = false;
			if (ft_strcmp(s_line[p->i], "\'\'") == 0
				|| ft_strcmp(s_line[p->i], "\"\"") == 0)
				s_line[p->i] = " ";
			if (s_line[p->i + 1])
				dprintf(p->outfile, "%s ", s_line[p->i]);
			else
				dprintf(p->outfile, "%s", s_line[p->i]);
			p->i++;
		}
		if (p->with_nl)
			dprintf(p->outfile, "\n");
		g_ex.status = 0;
	}
	if (local == false)
		exit_echo_child(p);
}
