/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adube <adube@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:42:51 by pirichar          #+#    #+#             */
/*   Updated: 2024/08/19 14:36:57 by adube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Bubble sort strings array
			called by env.c and export.c
 * 
 * @param sorted array of strings
 * @return unsorted array of strings
 */
char	**bubble_sort_strarr(char **rtn)
{
	int		i;
	char	*tmp;

	i = 0;
	while (rtn[i + 1])
	{
		if (ft_strcmp(rtn[i], rtn[i + 1]) > 0)
		{
			tmp = rtn[i];
			rtn[i] = rtn[i + 1];
			rtn[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
	return (rtn);
}

/**
 * @brief Helper static function for print export
			Will malloc a copy of to_sort
			and pass it to bubble_sort_strarr
			I don't get why I do this this way
 * 
 // TO-DO  THE LOGIC HERE IS FUCKED TOP
 	WHY DONT I PASS RTN BY ADDRESS TO SORT_STRARR
 * @param to_sort 
 * @return char** 
 */
static char	**sort_strarr(char **to_sort)
{
	int		i;
	char	**rtn;

	i = 0;
	while (to_sort && to_sort[i])
		i++;
	rtn = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (to_sort[i])
	{
		rtn[i] = ft_strdup(to_sort[i]);
		i++;
	}
	return (bubble_sort_strarr(rtn));
}

/**
 * @brief will print the env vars sorted by sort_starr
 * 
 * @param new_env to print
 */
static void	print_export(char ***new_env, t_parsing *p)
{
	char	**to_print;
	int		i;

	i = 0;
	to_print = sort_strarr(*new_env);
	while (to_print[i])
	{
		ft_putstr_fd("declare -x", p->outfile);
		ft_putstr_fd(to_print[i], p->outfile);
		ft_putstr_fd("\n", p->outfile);
		i++;
	}
	free_strrarr(to_print);
}

/**
 * @brief Function called to set variable into our env
 * 
 * @param s_line splitted cmd line
 * @param new_env the env to add the variable
 */
static void	actually_set_variables(char **s_line, char ***new_env, t_parsing *p)
{
	p->i = 1;
	while (s_line[p->i])
	{
		p->to_add = ft_export_split(s_line[p->i], '=');
		if (p->to_add[0] == NULL)
		{
			ft_putstr_fd("DunderSHell: export: `=': not a valid identifier\n",
				STDERR_FILENO);
			g_ex.status = 1;
		}
		else if (p->to_add[1] != NULL)
		{
			p->to_add[0] = ft_strjoin_free(p->to_add[0], "=");
			set_variable(new_env, p->to_add[0], p->to_add[1]);
		}
		else if (p->to_add[1] == NULL)
		{
			p->to_add[0] = ft_strjoin_free(p->to_add[0], "=");
			set_variable(new_env, p->to_add[0], "");
		}
		g_ex.status = 0;
		free_strrarr(p->to_add);
		p->i++;
	}
}

/**
 * @brief Builtin function
			Our version of export
			will call print export with no argument
			else will call actually_set_variables
 * 
 * @param s_line splitted cmd line
 * @param new_env the env since we want to export in it
 * @param parse for the builtin bool
 */
void	mini_export(char **s_line, char ***n_env, t_parsing *p, bool loc)
{
	p->b_in = true;
	p->bin_do_not_wait = true;
	if (s_line[1] == NULL && loc)
		print_export(n_env, p);
	else if (loc)
		actually_set_variables(s_line, n_env, p);
	if (!loc)
	{
		arena_free(&g_ex.arena);
		free_strrarr(g_ex.new_env);
		exit (g_ex.status);
	}
}
