/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:14:13 by pirichar          #+#    #+#             */
/*   Updated: 2022/06/12 14:32:48 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	strarr_len(char **str_arr)
{
	int i;

	i = 0;
	while(str_arr[i])
		i++;
	return (i);
}

static void	add_new_variable(char **env,char *var, char *variable)
{
	int i;
	char **tmp;
	
	tmp = env;
	i = strarr_len(env);
	env = malloc(sizeof(char *) * i + 2);
	env[i + 2] = 0;
	i = 0;
	while(tmp[i])
	{
		env[i] = ft_strdup(tmp[i]);
		i++;
	}
	env[i] = ft_strjoin(var, variable);
	//free tmp probably here
}

void	set_variable(char **env, char *var, char *new_var)
{
	int i;
	char *tmp;

	i = 0;
	while(env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
		{
			tmp = env[i];
			env[i] = ft_strjoin(var, new_var);
			free(tmp);
			break;
		}
		i++;
	}
	add_new_variable(env, var, new_var);
	//look for variable first
	//if you find it replace it
	//if you dont find it create it 
		//create a new array 
}

void	mini_cd(char **s_line, char **new_env)
{
	/*change the OLDPWD= folder*/
	char *actual_pwd;
	char *buff;
	
	buff = NULL;
	actual_pwd = getcwd(buff, 1024);
	set_variable(new_env, "OLDPWD=", actual_pwd);
	free(actual_pwd);
	free(buff);
	chdir(s_line[1]);
	/*change the PWD*/
	buff = NULL;
	actual_pwd = getcwd(buff, 1024);
	set_variable(new_env, "PWD=", actual_pwd);
	free(actual_pwd);
	free(buff);
}
//s'assurer que dans la version officielle echo "-n" 
// fonctionne aussi mais pas echo " -n"
void	mini_echo(char **s_line)
{
	int i;

	i = 1;
	bool with_nl = true;
	while(s_line[i])
	{
		//filter un nombre inifni de -n
		//fitrer un nombre infini de n dans le flag -n
		//-n had to be at the start
		if (ft_strncmp(s_line[i], "-n", 3) == 0)
		{
			with_nl = false;
			i++;
		}
		if (s_line[i] != 0)
		printf("%s ", s_line[i++]);
	}
	if (with_nl)
		printf("\n");
}


void	mini_pwd()
{
	char *to_print;
	char *buff;
	
	buff = NULL;
	to_print = getcwd(buff, 1024);
	printf("%s\n",to_print);
	free(to_print);
	free(buff);
}

void	mini_env(char **new_env)
{
	int i;

	i = 0;
	while(new_env[i])
	{
		printf("%s\n",new_env[i]);
		i++;
	}
	printf("\n");
}

void	look_for_builtins(char **s_line, char **new_env, bool *b_in)
{

	if(ft_strncmp(s_line[0], "echo",5) == 0)
	{
		*b_in = true;
		mini_echo(s_line);
	}
	else if(ft_strncmp(s_line[0], "cd",3) == 0)
	{
		*b_in = true;
		mini_cd(s_line, new_env);
	}
	else if(ft_strncmp(s_line[0], "export",8) == 0)
	{
		*b_in = true;
		//if no command just show all the Standard variables
	}
	else if(ft_strncmp(s_line[0], "unset",6) == 0)
	{
		*b_in = true;
		//if no command just show all the Standard variables
	}
	else if(ft_strncmp(s_line[0], "pwd",4) == 0)
	{
		*b_in = true;
		mini_pwd();
	}
	else if (ft_strncmp(s_line[0], "env",5) == 0)
	{
		*b_in = true;
		mini_env(new_env);
	}
}