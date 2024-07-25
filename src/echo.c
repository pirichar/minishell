/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:43:32 by pirichar          #+#    #+#             */
/*   Updated: 2024/07/25 11:43:33 by pirichar         ###   ########.fr       */
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

/**
 * @brief This function basically printf stuff
			It first look for -n -nnn and multiples -n
			Then once it filtered all the -n
			After that it set check_nl to false
			this way it does not look for flags
			to parse but print them out instead
			So our echo act more like zsh then bash its a decision we made
			Because of -n -n -n working 
 * @param s_line line to print
 * @param parse used to check the NEW LINE and to set the b_in is true
 */
void	mini_echo(char **s_line, t_parsing *parse)
{
	int		i;

	i = 1;
	parse->with_nl = true;
	parse->check_nl = true;
	parse->b_in = true;
	parse->bin_do_not_wait = true;
	while (s_line[i])
	{
		parse_echo(s_line, &parse->check_nl, &parse->with_nl, &i);
		if (s_line[i] == NULL)
			return ;
		parse->check_nl = false;
		if (s_line[i + 1])
			dprintf(parse->outfile, "%s ", s_line[i]);
		else
			dprintf(parse->outfile, "%s", s_line[i]);
		i++;
	}
	if (parse->with_nl)
		dprintf(parse->outfile, "\n");
}
