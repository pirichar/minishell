/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 10:06:15 by pirichar          #+#    #+#             */
/*   Updated: 2022/06/09 12:18:41 by pirichar         ###   ########.fr       */
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
	int	i;

	i = 0;
	while (path[i])
		i++;
	return (i);
}

int	main(int argc, char **argv, char **env)
{
	
	(void)argc;
	(void)argv;
	int		i;
	char	*line;
	char **path;
	char **s_line;
	char **new_env;
	bool	b_in;


	print_logo(env);
	new_env = copy_strarr(env);
	while (1)
	{
		b_in = false;
		path = var_to_strarr(new_env,"PATH=");
		i = 0;
		line = readline("MINISHELL: ");
		if (line == NULL)
			return (0);
		if (line && *line)
		{ 
			add_history(line);
			if (line == NULL)
			{
				free (s_line);
				free(line);
				return (0);
			}
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
				
				while(path[i])
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
			free(line);
		}
		else
			free(line);
	}
	free(path);
}

void	print_logo(char **env)
{
	char	*lol[15];
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		lol[0] = "/usr/bin/clear";
		lol[1] = NULL;
		execve("/usr/bin/clear", lol, env);
	}
	wait(NULL);
	printf("\n __________________________________________________________________\n");
	printf("|    ____                  __             __  ____ ___________     |\n");
	printf("|   / __ \\__  ______  ____/ /__  _____   /  |/  (_) __/ __/ (_)___ |\n");
	printf("|  / / / / / / / __ \\/ __  / _ \\/ ___/  / /|_/ / / /_/ /_/ / / __ \\|\n");
	printf("| / /_/ / /_/ / / / / /_/ /  __/ /     / /  / / / __/ __/ / / / / /|\n");
	printf("|/_____/\\____/_/ /_/\\__,_/\\___/_/   __/_/  /_/_/_/ /_/ /_/_/_/ /_/ |\n");
	printf("|        / /_  __  __   _________ _/ /_  ________                  |\n");
	printf("|       / __ \\/ / / /  / ___/ __ `/ __ \\/ ___/ _ \\                 |\n");
	printf("|      / /_/ / /_/ /  (__  ) /_/ / /_/ / /  /  __/                 |\n");
	printf("|     /_.___/\\__, /  /____/\\__,_/_.___/_/   \\___/                  |\n");
	printf("|          /____/                                                  |\n");
	printf("|__________________________________________________________________|\n\n\n");
}