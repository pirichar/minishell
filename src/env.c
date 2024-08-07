/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:43:29 by pirichar          #+#    #+#             */
/*   Updated: 2024/07/25 11:43:30 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Basically just go through all the new_env and print everything
 * 
 * @param new_env The new env to print
 * @param parse to set the b_in to true
 */
void	mini_env(char **new_env, t_parsing *parse)
{
	int		i;
	char	**tmp;

	parse->b_in = true;
	i = 0;
	while (new_env[i])
	{
		tmp = ft_split(new_env[i], '=');
		if (tmp[1] != NULL)
			dprintf(parse->outfile, "%s\n", new_env[i]);
		free_strrarr(tmp);
		i++;
	}
}

/**
 * @brief Helper function called in export.c by bubble_sort_strarr
			Here since it was not in the libft, should be there
 * 
 * @param s1 to cmpr 
 * @param s2 to cmpr
 * @return int 
  // TO-DO MOVE TO LIBFT
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/**
 * @brief Add new variable to the env ONLY CALLED BY SET_VARIABLE

 * @param env Pointer to the char** env 
 * @param var Variable to set
 * @param variable its value
 */
static void	add_new_variable(char ***env, char *var, char *value)
{
	int		i;
	char	**tmp;

	tmp = *env;
	i = strarr_len(*env);
	(*env) = ft_calloc(i + 2, sizeof(char *));
	i = 0;
	while (tmp[i])
	{
		(*env)[i] = ft_strdup(tmp[i]);
		i++;
	}
	(*env)[i] = ft_strjoin(var, value);
	free_strrarr(tmp);
}

/**
 * @brief Set or add a new variable with EXPORT popa=MOMAN
 * 
 * @param env env variables passed by pointer
 * @param var variable to set
 * @param new_var 
 */
void	set_variable(char ***env, char *var, char *new_var)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], var, ft_strlen(var)) == 0)
		{
			tmp = (*env)[i];
			(*env)[i] = ft_strjoin(var, new_var);
			free(tmp);
			break ;
		}
		i++;
	}
	if ((*env)[i] == NULL)
		add_new_variable(env, var, new_var);
}
