/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 10:06:15 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/31 16:26:26 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "../include/minishell.h"

// void	print_env()
// {
// 	char	*tmp;


// }

// int main(int argc, char **argv, char **env)
// {
// 	(void)argc;
// 	(void)argv;
// 	char *line;
// 	int		i;
// 	char **path;	
// 	path = path_to_strarr(env);
// 	i = 0;
// 	while(1)
// 	{
// 		line = readline("MINISHELL: ");
// 		if (line && *line) // not sure I need this but saw it in the man
// 			add_history(line);
// 		while(path[i])
// 		{
// 			if (search_path(path[i], line) == true)
// 				printf("VALID COMMAND WILL HANDLE LATER\n");
// 			else
// 				printf("Invalid command\n");
// 			i++;
// 		}
// 		if (ft_strncmp(line, "env",5) == 0)
// 		{
// 			i = 0;
// 			while(env[i])
// 			{
// 				printf("%s\n",env[i]);
// 				i++;
// 			}
// 			printf("\n");
// 			free(line);
// 		}
// 		else if(ft_strncmp(line, "exit",5) == 0)
// 		{
// 			free(line);
// 			return (0);
// 		}
// 		else
// 			free(line);
// 	}
// 	free(path);
// }


int	nb_of_paths(char **path)
{
	int i;

	i = 0;
	while(path[i])
		i++;
	return (i);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char *line;
	int		i;
	char **path;
	
	path = path_to_strarr(env);
	while(1)
	{
		i = 0;
		line = readline("MINISHELL: ");
		if (line && *line) // not sure I need this but saw it in the man
			add_history(line);
		/* parse the line here
			1- first round check the special characters
			2- reparse taking in count special character and fill the cmd array
			3- give that to the command that search the path
							*/
		/* 
			initiate program for this and work in the child after
			create an array of pids
			pass the array of argument as it was char **argv in calling_the_execs
			Calculate the amount of argument and pass it as argc 
		*/
		while(path[i])
		{
			if (search_path(path[i], line) == true)
				break ;
			i++;
		}
		if (i == nb_of_paths(path))
				printf("Invalid command\n");
		else
		{
			printf("VALID COMMAND WILL HANDLE LATER\n");
			//here I should probably fork and start to do stuff with that command
		}

		if (ft_strncmp(line, "env",5) == 0)
		{
			i = 0;
			while(env[i])
			{
				printf("%s\n",env[i]);
				i++;
			}
			printf("\n");
			free(line);
		}
		else if(ft_strncmp(line, "exit",5) == 0)
		{
			free(line);
			return (0);
		}
		else
			free(line);
	}
	free(path);
}