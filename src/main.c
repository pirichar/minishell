#include "../include/minishell.h"

int	nb_of_charstrstr(char **path)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	return (i);
}

static void	wait_for_pids(t_parsing *parse)
{
	int	i;

	i = 0;
	while (i <= parse->nb_of_pipes)
	{
		waitpid(parse->pids[i], &parse->status, 0);
		i++;
	}
	if (parse->infile != 0)
		close(parse->infile);
	free(parse->pids);
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	char	*line;
	char	**path;
	char	**s_line;
	char	**new_env;
	char	*prompt;
	int		status;
	t_parsing 	*parse;
	// pid_t	p;

	status = 0;
	if (argc > 1)
	{
		fprintf(stderr, "Why U put params?!?!\n");
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
		line = readline(prompt);
		free(prompt);
		if (line == NULL)
		{
			free(line);
			free_strrarr(new_env);
			return (0);
		}
		if (*line)
		{
			add_history(line);
			parse = start_parse(line, status);
			if (parse == NULL)
			{
				free(line);
				continue;
			}
			//on dirait que vector_cmd c'est celui du dernier list qui est passé
			s_line = parse->tkns_list->vector_cmd;// yen a combien de vctor cmd de creers
			if (s_line[0] == NULL)
			{
				free(line);
				free_strrarr(s_line);
				continue ;
			}
			look_for_builtins(&line, &s_line, &new_env, parse);
			//basic execute function
			if (parse->b_in == false)
			{
				i = 0;
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
						parse->cmd = true;
						calling_the_execs_shell(s_line, new_env, parse);
						wait_for_pids(parse);
					}
				}
			}
			if (parse->b_in == false && parse->cmd == false)
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