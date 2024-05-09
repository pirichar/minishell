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
	path = calloc(sizeof(char), len);
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

/*
	Basically the same as getenv() but you pass
	the environment table you want as the first argument
	then pass the variable you look for
	The functions return a pointer to the variable 
	or NULL if nothing is found
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

/*
	This function takes as input a line of the path
	and the argv[1] passed by main
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

bool	search_path_exec(const char *p_arr, const char *cmd)
{
	char	*line;

	line = ft_strjoin(p_arr, cmd);
	if (access(line, X_OK) == 0)
	{
		free(line);
		return (true);
	}
	free(line);
	return (false);
}
