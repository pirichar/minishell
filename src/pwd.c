/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:42:08 by pirichar          #+#    #+#             */
/*   Updated: 2024/07/25 11:42:10 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
* @brief Builtin function
		Our version of PWD
		Using getCWD to get it
 * 
 * @param parse to set b_in true
 */
void	mini_pwd(t_parsing *parse)
{
	char	*to_print;
	char	*buff;

	parse->b_in = true;
	buff = NULL;
	to_print = getcwd(buff, 1024);
	printf("%s\n", to_print);
	free(to_print);
	free(buff);
}

void	set_old_pwd(char ***new_env)
{
	char	*actual_pwd;
	char	*buff;

	buff = NULL;
	actual_pwd = getcwd(buff, 1024);
	set_variable(new_env, "OLDPWD=", actual_pwd);
	free(actual_pwd);
	free(buff);
}

void	set_pwd(char ***new_env)
{
	char	*actual_pwd;
	char	*buff;

	buff = NULL;
	actual_pwd = getcwd(buff, 1024);
	set_variable(new_env, "PWD=", actual_pwd);
	free(actual_pwd);
	free(buff);
}

char	*get_cwd(void)
{
	char	*actual_pwd;
	char	*buff;

	buff = NULL;
	actual_pwd = getcwd(buff, 1024);
	free(buff);
	return (actual_pwd);
}
