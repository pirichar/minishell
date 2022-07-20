#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "../include/minishell.h"

int	nb_of_charstrstr(char **path)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	return (i);
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	char	*line;
	char	**path;
	char	**s_line;
	char	**new_env;
	char	*prompt;
	bool	b_in;
	pid_t	p;

	if (argc > 1)
	{
		printf("Why U put params?!?!\n");
		return (1);
	}
	(void)argv;
	print_logo(env);
	//set the env
	new_env = copy_strarr(env);
	//start the loop
	while (1)
	{
		prompt = set_prompt(new_env);
		b_in = false;
		i = 0;
		line = readline(prompt);
		free(prompt);
		if (line == NULL)
		{
			free(line);
			free(new_env);
			return (0);
		}
		if (line && *line)
		{
			add_history(line);
			start_parse(line);
			s_line = ft_split(line, ' ');
			if (s_line[0] == NULL)
				continue ;
			look_for_builtins(s_line, &new_env, &b_in);
			if (ft_strncmp(s_line[0], "exit",5) == 0)
			{
				free (s_line);
				free(line);
				return (0);
			}
			//basic execute function
			if (b_in == false)
			{
				i = 0;
				path = var_to_strarr(new_env, "PATH=");
				if (path == NULL)
					printf("TERM environment variable not set\n");
				else
				{
					while (path[i])
					{
						if (search_path(path[i], s_line[0]) == true)
							break ;
						i++;
					}
					if (i != nb_of_charstrstr(path))
					{
						execute_solo(line, &p, new_env);
						waitpid(p, NULL, 0);
					}
				}
			}
			else if (b_in == false)
			{
				printf("Please provide a built-in command to test or a valid command in the path\n");
			}
			free(s_line);
			free(line);
		}
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
		execve(lol[0], lol, env);
	}
	wait(NULL);
	printf(RED"\n __________________________________________________________________\n");
	printf("|    ____                  __             __  ____ ___________     |\n");
	printf("|   / __ \\__  ______  ____/ /__  _____   /  |/  (_) __/ __/ (_)___ |\n");
	printf("|  / / / / / / / __ \\/ __  / _ \\/ ___/  / /|_/ / / /_/ /_/ / / __ \\|\n");
	printf("| / /_/ / /_/ / / / / /_/ /  __/ /     / /  / / / __/ __/ / / / / /|\n");
	printf("|/_____/\\____/_/ /_/\\__,_/\\___/_/   __/_/  /_/_/_/ /_/ /_/_/_/ /_/ |\n");
	printf(BLU"|        / /_  __  __   _________ _/ /_  ________                  |\n");
	printf("|       / __ \\/ / / /  / ___/ __ `/ __ \\/ ___/ _ \\                 |\n");
	printf("|      / /_/ / /_/ /  (__  ) /_/ / /_/ / /  /  __/                 |\n");
	printf("|     /_.___/\\__, /  /____/\\__,_/_.___/_/   \\___/                  |\n");
	printf("|          /____/                                                  |\n");
	printf("|__________________________________________________________________|\n\n\n"RESET);
}