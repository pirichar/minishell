#include <stdbool.h>
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
	bool	b_in;
	bool	cmd;
	char	*user;
	char	*pwd;
	char	*blue_user;
	char	*with_at;
	char	*prompt;

	(void)argv;
	(void)argc;
	print_logo(env);
	i = 0;
	//set the env
	new_env = copy_strarr(env);
	//set the prompt
	while (new_env[i] && ft_strncmp(new_env[i], "USER=", 5))
		i++;
	if (new_env[i])
	{
		user = calloc(ft_strlen(env[i]), sizeof(char));
		ft_strlcpy(user, env[i] + 5, ft_strlen(env[i]));
		blue_user = ft_strjoin(BBLU, user);
		free(user);
		prompt = ft_strjoin(blue_user, "\e[1;31m@\e[1;32mDunderShell>$ \e[0m");
		free(blue_user);
	}
	else
		prompt = ft_strdup("DunderShell = ");

	//start the loop
	while (1)
	{
		i = 0;
		while (ft_strncmp(new_env[i], "USER=", 5))
			i++;
		user = calloc(ft_strlen(new_env[i]), sizeof(char));
		ft_strlcpy(user, new_env[i] + 5, ft_strlen(new_env[i]));
		blue_user = ft_strjoin(BBLU, user);
		free(user);
		i = 0;
		while (ft_strncmp(new_env[i], "PWD=", 4))
			i++;
		user = calloc(ft_strlen(new_env[i]), sizeof(char));
		ft_strlcpy(user, new_env[i] + 4, ft_strlen(new_env[i]));
		with_at = ft_strjoin(blue_user, "\e[1;31m@\e[1;32m");
		pwd = ft_strjoin(user, " $> \e[0m");
		prompt = ft_strjoin(with_at, pwd);
		free(blue_user);
		free(with_at);
		free(pwd);
		free(user);
		b_in = false;
		cmd = false;
		i = 0;
		line = readline(prompt);
		free(prompt);
		if (line == NULL)
		{
			free(line);
			free_strrarr(new_env);
			return (0);
		}
		if (line && *line)
		{
			add_history(line);
			start_parse(line);
			s_line = ft_split(line, ' ');
			if(s_line[0] == NULL)
			{
				free(line);
				free_strrarr(s_line);
				continue;
			}
			look_for_builtins(&line, &s_line, &new_env, &b_in);
			//basic execute function
			if (b_in == false)
			{
				i = 0;
				pid_t p;
				path = path_to_starrr(new_env, "PATH=");
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
					if (i != nb_of_charstrstr(path) || access(s_line[0], X_OK) == 0)
					{
						cmd = true;
						execute_solo(line, &p, new_env);
						waitpid(p, NULL, 0);
					}
				}
			}
			if (b_in == false && cmd == false)
				printf("Please provide a built-in command to test or a valid command in the path\n");
		free_strrarr(s_line);
		}
		free(line);
	}
	free_strrarr(path);
	free(prompt);
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