/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:41:54 by pirichar          #+#    #+#             */
/*   Updated: 2024/07/25 11:41:54 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief returns a copy of a variable or null if not found
			Used in builtin.c, cd.c and unset.c
 * 
 * @param env variables to look into
 * @param var to search
 * @return Copy of a vraible or null
 */
char	*return_variable(char **env, char *var)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
		{
			return (env[i]);
		}
		i++;
	}
	return (NULL);
}

/**
 * @brief 
 * 
 * @param env 
 * @param var 
 */
static void	delete_variable(char ***env, char *var)
{
	int		i;
	int		j;
	char	**tmp;

	tmp = *env;
	i = strarr_len(*env);
	(*env) = ft_calloc(i, sizeof(char *));
	i = 0;
	j = 0;
	while (tmp[i])
	{
		if (ft_strncmp(tmp[i], var, ft_strlen(var)) != 0)
		{
			(*env)[j] = ft_strdup(tmp[i]);
			i++;
			j++;
		}
		else
			i++;
	}
	if (i != strarr_len(*env))
		free_strrarr(tmp);
}

/**
 * @brief Builtin function
			Our version of unset
			Will first check if enough arguments
			Then will loop over everything to unset
			If we try to unset = we will give an error
 * 
 // TO-DO Double check the behavior with = like
 popa=moman or === , bash wont unset if there is at least one
 = in the stuff to unset this is not my behavior
 * @param s_line 
 * @param new_env 
 * @param p parsing struct used for the i, 
 */
void	mini_unset(char **s_line, char ***new_env, t_parsing *p, bool local)
{
	p->b_in = true;
	p->bin_do_not_wait = true;
	if (s_line[1] == NULL)
	{
		fprintf(stderr, "unset : not enough arguments\n");
		g_ex.status = 1;
	}
	else
	{
		p->i = 1;
		while (s_line[p->i])
		{
			if (s_line[p->i] && s_line[p->i][0] == '=' &&
					s_line[p->i][1] == '\0')
			{
				fprintf(stderr, "Minishell: unset: \"=\": not a valid identifier\n");
				p->i++;
				g_ex.status = 1;
				continue ;
			}
			p->to_unset = return_variable((*new_env), s_line[p->i]);
			if (p->to_unset != NULL)
				delete_variable(new_env, s_line[p->i]);
			p->i++;
			g_ex.status = 0;
		}
	}
	if (!local)
	{
		arena_free(&g_ex.arena);
		free_strrarr(g_ex.new_env);
		exit (g_ex.status);
	}
}
