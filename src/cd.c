/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adube <adube@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:43:35 by pirichar          #+#    #+#             */
/*   Updated: 2024/08/20 10:25:11 by adube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>

/**
 * @brief function called by CD when no option with it
 * 
 * @param new_env passwd to set the PWD
 */
static void	go_to_home(char ***new_env)
{
	char	**home;
	char	*actual_pwd;

	home = ft_split(return_variable(*new_env, "HOME"), '=');
	if (home == NULL)
		printf("minishell: cd: HOME not set\n");
	else
	{
		chdir(home[1]);
		free_strrarr(home);
	}
	actual_pwd = get_cwd();
	set_variable(new_env, "PWD=", actual_pwd);
	free(actual_pwd);
}

/**
 * @brief Check permissions to local folder and verify users demand
			will call stat to check the folder permission and verify we asked ..
 * 
 * @param file wich is the command or where the user is trying to go
 * @return 0 of its fine 1 if we encounter a locked folder with the cd .. 
 */
static int	check_persmissions(char *file)
{
	char		*actual_pwd;
	struct stat	statbuff;

	actual_pwd = get_cwd();
	if (stat(".", &statbuff) == -1 && ft_strcmp(file, "..") == 0)
	{
		free(actual_pwd);
		return (1);
	}
	free(actual_pwd);
	return (0);
}

/**
 * @brief 	//remove the end of the pwd to go backwards
			//get the strlen;
			//do a copy
			//then start from the revert index to find the first /
 * 
 * @param parse 
 * @return int 
 */
static int	chmod_situation(t_parsing *parse)
{
	int		rtn;
	char	*pwd;
	int		pwd_len;
	int		to_trim;
	int		tmp;

	to_trim = 0;
	pwd = get_cwd();
	pwd_len = ft_strlen(pwd);
	tmp = pwd_len;
	parse->up_dir = ft_calloc(1, pwd_len +1);
	while (tmp)
	{
		tmp--;
		to_trim++;
		if (pwd[tmp] == '/')
			break ;
	}
	ft_strlcpy(parse->up_dir, pwd, pwd_len - to_trim + 1);
	rtn = chdir(parse->up_dir);
	free(parse->up_dir);
	free(pwd);
	return (rtn);
}

static void	cd_err(char *s_line)
{
	g_ex.status = 1;
	ft_putstr_fd(ft_strjoin_arena("cd: no such file or directory: ", s_line),
		STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
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
void	mini_cd(char **s_line, char ***new_env, t_parsing *parse, bool local)
{
	int		rtn;

	rtn = 0;
	parse->b_in = true;
	parse->bin_do_not_wait = true;
	set_old_pwd(new_env);
	if (s_line[1] == NULL)
	{
		go_to_home(new_env);
		return ;
	}
	else if (check_persmissions(s_line[1]) == 1)
		rtn = chmod_situation(parse);
	else if (s_line[1])
		rtn = chdir(s_line[1]);
	if (rtn != 0)
		cd_err(s_line[1]);
	else
		g_ex.status = 0;
	set_pwd(new_env);
	if (!local)
		clean_and_exit(g_ex.status);
}
