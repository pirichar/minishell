/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:43:35 by pirichar          #+#    #+#             */
/*   Updated: 2024/07/25 11:43:36 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief function called by CD when no option with it
 * 
 * @param new_env passwd to set the PWD
 */
static void	go_to_home(char ***new_env)
{
	char	**home;
	char	*actual_pwd;
	char	*buff;

	home = ft_split(return_variable(*new_env, "HOME"), '=');
	if (home == NULL)
		printf("minishell: cd: HOME not set\n");
	else
	{
		chdir(home[1]);
		free_strrarr(home);
	}
	buff = NULL;
	actual_pwd = getcwd(buff, 1024);
	set_variable(new_env, "PWD=", actual_pwd);
	free(actual_pwd);
	free(buff);
}

/**
 * @brief Builtin function
			our version of CD;
			It used to change directory with every argument 
			like cd .. folder .. folder would get you back to folder
			But now its only one argument or getting you back to home
 * 
 * @param s_line splitted cmd line
 * @param new_env the env passed by address
 * @param parse for the b_in bool
 */
void	mini_cd(char **s_line, char ***new_env, t_parsing *parse)
{
	char	*actual_pwd;
	char	*buff;

	parse->b_in = true;
	parse->bin_do_not_wait = true;
	buff = NULL;
	actual_pwd = getcwd(buff, 1024);
	set_variable(new_env, "OLDPWD=", actual_pwd);
	free(actual_pwd);
	free(buff);
	if (s_line[1] == NULL)
	{
		go_to_home(new_env);
		return ;
	}
	if (s_line[1])
		chdir(s_line[1]);
	buff = NULL;
	actual_pwd = getcwd(buff, 1024);
	set_variable(new_env, "PWD=", actual_pwd);
	free(actual_pwd);
	free(buff);
}
