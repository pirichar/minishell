/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:44:05 by pirichar          #+#    #+#             */
/*   Updated: 2024/07/25 11:44:06 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdbool.h>

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

/**
 * @brief Basically what the name of the function says , not bad eh?
			This function is called from execution functions
			Echo
			Cd
			Export
			Unset
			pwd
			env
			exit
			$
 * 
 * @param s_line Pointer to the Char** cmd
 * @param new_env the env whihc is needed in some builtins
 * @param parse  the parse structure so I can set builtin to true
 */
void	look_for_builtins(char ***s_line, char ***new_env, t_parsing *parse)
{
	if (ft_strcmp(*s_line[0], "echo") == 0)
		mini_echo(*s_line, parse);
	else if (ft_strcmp(*s_line[0], "cd") == 0)
		mini_cd(*s_line, (new_env), parse);
	else if (ft_strcmp(*s_line[0], "export") == 0)
		mini_export(*s_line, (new_env), parse);
	else if (ft_strcmp(*s_line[0], "unset") == 0)
		mini_unset(*s_line, new_env, parse);
	else if (ft_strcmp(*s_line[0], "pwd") == 0)
		mini_pwd(parse);
	else if (ft_strcmp(*s_line[0], "env") == 0)
		mini_env((*new_env), parse);
	else if (ft_strcmp(*s_line[0], "exit") == 0)
		mini_exit(*s_line, parse);
}
