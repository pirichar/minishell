
#include "../include/minishell.h"

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
	int		i;
	char	*line;
	char	**path;
	char	**s_line;
	char	**new_env;
	bool	b_in;
	char	*user;
	char	*blue_user;
	char	*prompt;

	(void)argv;
	(void)argc;
	print_logo(env);
	i = 0;
	while (ft_strncmp(env[i], "USER=", 5))
		i++;
	user = calloc(ft_strlen(env[i]), sizeof(char));
	ft_strlcpy(user, env[i] + 5, ft_strlen(env[i]));
	blue_user = ft_strjoin(BBLU, user);
	free(user);
	prompt = ft_strjoin(blue_user, "\e[1;31m@\e[1;32mDunderShell>$ \e[0m");
	free(blue_user);
	new_env = copy_strarr(env);
	while (1)
	{
		b_in = false;
		path = var_to_strarr(new_env, "PATH=");
		i = 0;
		line = readline(prompt);
		if (line == NULL)
		{
			free(line);
			free(path);
			free(new_env);
			return (0);
		}
		if (line && *line)
		{
			add_history(line);
			start_parse(line, env);




			s_line = ft_split(line, ' ');
			look_for_builtins(s_line, new_env, &b_in);
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
				pid_t p;
				while (path[i])
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