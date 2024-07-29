/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look_for.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:42:36 by pirichar          #+#    #+#             */
/*   Updated: 2024/07/25 11:42:36 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/**
 * @brief General note :
			Helper functions called by execute SOLO
 */

/**
 * @brief Looking for exit
			Only called in execute solo
 * 
 * @param s_line splitted command to look into
 * @return true if the first line is exit
 * @return false if its not
 */
bool	look_for_exit(char **s_line)
{
	if (ft_strcmp(s_line[0], "exit") == 0)
	{
		return (true);
	}
	return (false);
}

/**
 * @brief Looking for export
			Only called in execute solo
 * 
 * @param s_line splitted command to look into
 * @return true if the first line is export
 * @return false if its not
 */
bool	look_for_export(char **s_line)
{
	if (ft_strcmp(s_line[0], "export") == 0)
	{
		return (true);
	}
	return (false);
}

/**
 * @brief Looking for unset
			Only called in execute solo
 * 
 * @param s_line splitted command to look into
 * @return true if the first line is unset
 * @return false if its not
 */
bool	look_for_unset(char **s_line)
{
	if (ft_strcmp(s_line[0], "unset") == 0)
	{
		return (true);
	}
	return (false);
}

/**
 * @brief Looking for cd
			Only called in execute solo
 * 
 * @param s_line splitted command to look into
 * @return true if the first line is cd
 * @return false if its not
 */
bool	look_for_cd(char **s_line)
{
	if (ft_strcmp(s_line[0], "cd") == 0)
	{
		return (true);
	}
	return (false);
}

/**
 * @brief Looking for echo
			Only called in execute solo
 * 
 * @param s_line splitted command to look into
 * @return true if the first line is echo
 * @return false if its not
 */
bool	look_for_echo(char **s_line)
{
	if (ft_strcmp(s_line[0], "echo") == 0)
	{
		return (true);
	}
	return (false);
}
