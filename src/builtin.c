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
bool	look_for_builtins(char ***s_line, char ***new_env, t_parsing *parse)
{
	bool	rtn;

	rtn = true;
	if (ft_strcmp(*s_line[0], "echo") == 0)
		mini_echo(*s_line, parse, false);
	else if (ft_strcmp(*s_line[0], "cd") == 0)
		mini_cd(*s_line, (new_env), parse, false);
	else if (ft_strcmp(*s_line[0], "export") == 0)
		mini_export(*s_line, (new_env), parse, false);
	else if (ft_strcmp(*s_line[0], "unset") == 0)
		mini_unset(*s_line, new_env, parse, false);
	else if (ft_strcmp(*s_line[0], "pwd") == 0)
		mini_pwd(parse);
	else if (ft_strcmp(*s_line[0], "env") == 0)
		mini_env((*new_env), parse);
	else if (ft_strcmp(*s_line[0], "exit") == 0)
		mini_exit(*s_line, parse, false);
	else
		rtn = false;
	return (rtn);
}
