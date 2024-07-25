/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:43:39 by pirichar          #+#    #+#             */
/*   Updated: 2024/07/25 11:43:39 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Return the lenght of the path
			This function is only used by path_to_starrr
 * 
 * @param env environement passed to search PATH
 * @return 1 or the strlen of the path
 // TO-DO There might be a better logic to implement
	Right now we do not check for the one in path to strarr
 */
static int	strlen_path(char **env)
{
	int	i;
	int	rtn;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			rtn = ft_strlen(env[i]);
			return (rtn);
		}
		i++;
	}
	return (1);
}

/**
 * @brief function that take as input the env variables passed by the main
			It will then look for the path into it; 
			find it strlen and malloc the proper size of string
			Then it will go again and find the path and 
			copy it into the malloced string
			It will then split the path removing the PATH= 
			to put it in p_arr which is a 2d ARRAY
			Finally it will free the string created 
			to split and return the 2d array 
			The output represent all the possible
			path to try with execve with the command
			This function is called by calling_the_execs_shell
			The var is only PATH= for now since its what we look for
 * 
 * @param env variables passed by the main
 * @param var PATH= is always passed for now
 * @return the splitted array of PATH splitted on : 
 */
char	**path_to_starrr(char **env, char *var)
{
	int		i;
	int		len;
	char	*path;
	char	**p_arr;

	p_arr = NULL;
	len = strlen_path(env);
	path = ft_calloc(sizeof(char), len);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
		{
			ft_strlcpy(path, env[i], len);
			p_arr = ft_split(path + 5, ':');
		}
		i++;
	}
	free (path);
	return (p_arr);
}

/**
 * @brief Basically the same as getenv() but you pass
			the environment table you want as the first argument
			then pass the variable you look for
			The functions return a pointer to the variable 
			or NULL if nothing is found
 * 
 * @param env env to look into 
 * @param var to look into env
 * @return a copy of the variable you found into env

 // TO-DO This function is dangerous I have no check in it
 */
char	*var_to_str(char **env, char *var)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
			break ;
		i++;
	}
	return (env[i]);
}

/**
 * @brief This function takes as input a line of the path
			It also takes as an input the CMD you are trying to look for
			It will add the slash to the cmd;
			do a strjoin of the path and the cmd 
			It will then try to acces it if it does it will return true
			Otherwise it will return false

			This function is called in parse_and_exec_cmd_shell
 * 
 * @param One of the avaialable Paths 
 * @param cmd to check with all the paths
 * @return true if we find are able to access the cmd
 * @return false if we can't acces the cmd
 */
bool	search_path_exec(const char *p_arr, const char *cmd)
{
	char	*line;

	line = ft_strjoin_arena(p_arr, cmd);
	if (access(line, X_OK) == 0)
		return (true);
	return (false);
}
