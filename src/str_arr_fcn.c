/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr_fcn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:42:05 by pirichar          #+#    #+#             */
/*   Updated: 2024/07/25 11:42:06 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "arena.h"

/**
 * @brief Return the lenght of an array of str
 * 
 * @param array of str to look into
 * @return lenght of the array 
 */
int	strarr_len(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr[i])
		i++;
	return (i);
}

/**
 * @brief Function to free an array of str
 * 
 * @param to_free to be free
 */
void	free_strrarr(char **to_free)
{
	int	i;

	i = 0;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
}

char	*ft_itoa_arena(long long n)
{
	char	*rtn;
	int		i;

	i = 0;
	rtn = arena_alloc(&g_ex.arena, 12);
	if (!rtn)
		return (NULL);
	if (n == 0)
	{
		rtn[0] = '0';
		i++;
	}
	if (n < 0)
	{
		rtn[i++] = '-';
		rtn[i++] = '0' - n % 10;
		n = n / -10;
	}
	while (n)
	{
		rtn[i] = n % 10 + '0';
		i++;
		n = n / 10;
	}
	return (ft_swap(rtn));
}
/**
 * @brief Local helper function
 			This function takes care of setting up
 			the 3 variables when we open the shell
			Those variables are
			PWD
			SHLVL
			_= (binary)
 * 
 * @param env passed by address by copy_env
 */

static void	set_3_variables(char ***env)
{
	char	*actual_pwd;
	char	*buff;
	char	*binary;
	char	*shlvl;
	int		nb;

	buff = NULL;
	actual_pwd = getcwd(buff, 1024);
	set_variable(env, "PWD=", actual_pwd);
	binary = ft_strjoin(actual_pwd, "./DunderShell");
	set_variable(env, "_=", binary);
	shlvl = var_to_str((*env), "SHLVL");
	if (shlvl == NULL)
		nb = 1;
	else
	{
		nb = shlvl[ft_strlen(shlvl) - 1] - '0';
		nb++;
	}
	shlvl = ft_itoa(nb);
	set_variable(env, "SHLVL=", shlvl);
	free(actual_pwd);
	free(buff);
	free(binary);
	free(shlvl);
}

/**
 * @brief This function copies the env variables passed by the main
			It then sets 3 variables that are the SHLVL, the actual pwd 
			and the binary using the function set 3 variabless
			Called by setup_minishell
 * 
 * @param env passed by main to be copied
 * @return char** 
 */
char	**copy_env(char **env)
{
	int		i;
	char	**rtn;

	i = 0;
	while (env && env[i])
		i++;
	rtn = ft_calloc((i + 1), sizeof(char *));
	if (i != 0)
	{
		i = 0;
		while (env[i])
		{
			rtn[i] = ft_strdup(env[i]);
			i++;
		}
	}
	set_3_variables(&rtn);
	return (rtn);
}
