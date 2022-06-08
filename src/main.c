/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 10:06:15 by pirichar          #+#    #+#             */
/*   Updated: 2022/06/08 15:18:11 by pirichar         ###   ########.fr       */
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

	new_env = copy_strarr(env);
	while(1)
	{
		path = var_to_strarr(new_env,"PATH=");
		i = 0;
		line = readline("MINISHELL: ");
		if (line && *line)
		{ // not sure I need this but saw it in the man
			add_history(line);
			s_line = ft_split(line, ' ');
			if(ft_strncmp(s_line[0], "echo",5) == 0)
			{
				//s'assurer que dans la version officielle echo "-n" 
				// fonctionne aussi mais pas echo " -n"
				i = 1;
				bool with_nl = true;
				while(s_line[i])
				{
					if (ft_strncmp(s_line[i], "-n", 4) == 0)
					{
						with_nl = false;
						i++;
					}
					printf("%s ", s_line[i++]);
				}
				if (with_nl)
					printf("\n");
			}
			
			else if(ft_strncmp(s_line[0], "cd",3) == 0)
			{
				// char *tmp;
				// char *actual_pwd;
				// char *pwd;
				// char *lpwd;
				// char *buff = NULL;

				// //UPDATE LAST PWD HERE?
				// tmp = *new_env;
				// lpwd = var_to_str(new_env, "OLDPWD=");
				// free(lpwd);
				// actual_pwd = getcwd(buff, 1024);
				// tmp = ft_strjoin("OLDPWD=",actual_pwd);
				// free(actual_pwd);
				chdir(s_line[1]);
				//update PWD HERE ?
				// pwd = var_to_str(new_env, "PWD=");

			}
			
			else if(ft_strncmp(s_line[0], "export",8) == 0)
			{
				//if no command just show all the Standard variables
			}
			else if(ft_strncmp(s_line[0], "unset",6) == 0)
			{
				//if no command just show all the Standard variables
			}
			else if(ft_strncmp(s_line[0], "pwd",4) == 0)
			{
				char *to_print;
				char *buff;
				
				buff = NULL;
				to_print = getcwd(buff, 1024);
				printf("%s\n",to_print);
				free(to_print);
				free(buff);
			}
			else if (ft_strncmp(s_line[0], "env",5) == 0)
			{
				//update PWD
				//faire une copie du ENV et l'updater
				i = 0;
				while(new_env[i])
				{
					printf("%s\n",new_env[i]);
					i++;
				}
				printf("\n");
			}
			else if(ft_strncmp(s_line[0], "exit",5) == 0)
			{
				free (s_line);
				free(line);
				return (0);
			}
			//basic execute function
			else if(1)
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
			else
			{
				printf("Please provide a built-in command to test or a valid command in the path\n");
				// free(line);
			}
		free(s_line);
		}
		free(line);
		free(path);
	}
}