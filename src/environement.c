/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:24:27 by pirichar          #+#    #+#             */
/*   Updated: 2022/06/08 15:26:00 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char **copy_strarr(char **env)
{
	int i;
	char **rtn;
	
	i = 0;
	while(env[i])
		i++;
	rtn = malloc(sizeof(char *) * i + 1);
	rtn[i + 1] = 0;
	i = 0;
	while(env[i])
	{
		rtn[i] = ft_strdup(env[i]);
		i++;
	}
	return (rtn);
}


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

/*
	function that take as input the environment variables passed by the main
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
*/
char	**var_to_strarr(char **env, char *var)
{
	int		i;
	int		len;
	char	*path;
	char	**p_arr;

	p_arr = NULL;
	len = strlen_path(env);
	path = malloc(sizeof(char) * len);
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

char	*var_to_str(char **env, char *var)
{
	while (env)
	{
		if (ft_strncmp(*env, var, ft_strlen(var)) == 0)
			break;
		env++;
	}
	return *(env);
}

/*
	This function takes as input a line of the path and the argv[1] passed by main
	It also takes as an input the CMD you are trying to look for
	It will add the slash to the cmd; do a strjoin of the path and the cmd 
	It will then try to acces it if it does it will return true
	Otherwise it will return false
*/
bool	search_path(const char *p_arr, const char *cmd)
{
	char	*line;
	char	*with_slash;

	with_slash = ft_strjoin("/", cmd);
	line = ft_strjoin(p_arr, with_slash);
	if (access(line, X_OK) == 0)
	{
		free(line);
		free(with_slash);
		return (true);
	}
	free(line);
	free(with_slash);
	return (false);
}
