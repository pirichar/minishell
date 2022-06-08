/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 10:06:15 by pirichar          #+#    #+#             */
/*   Updated: 2022/06/08 16:42:37 by pirichar         ###   ########.fr       */
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
	char **s_line;
	char **new_env;
	bool	b_in;


	new_env = copy_strarr(env);
	while(1)
	{
		b_in = false;
		path = var_to_strarr(new_env,"PATH=");
		i = 0;
		line = readline("MINISHELL: ");
		if (line && *line)
		{ // not sure I need this but saw it in the man
			add_history(line);
			s_line = ft_split(line, ' ');
			look_for_builtins(s_line, new_env, &b_in);
			if(ft_strncmp(s_line[0], "exit",5) == 0)
			{
				free (s_line);
				free(line);
				return (0);
			}
			//basic execute function
			if(b_in == false)
			{
				i = 0;
				pid_t p;
				//check if the command works line[0]
				while(path[i]) //this could be inserted into something else I used it to see if the command is in the path or not
				{
					if (search_path(path[i], s_line[0]) == true)
						break ;
					i++;
				}
				if (i != nb_of_paths(path))
				{
					execute_solo(line, &p, env);
					waitpid(p, NULL, 0);
				}
			}
			else if (b_in == false)
			{
				printf("Please provide a built-in command to test or a valid command in the path\n");
			}
		free(s_line);
		}
		free(line);
		free(path);
	}
}