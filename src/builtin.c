/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:14:13 by pirichar          #+#    #+#             */
/*   Updated: 2022/06/09 12:42:00 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	mini_cd(char **s_line)
{
	/*change the OLDPWD= folder*/
	chdir(s_line[1]);
	/*change the PWD*/

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
		mini_cd(s_line);
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