#include "../include/minishell.h"

int	nb_of_charstrstr(char **path)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	return (i);
}

/*
	So here we have 2 struct one for the execution and one for the parsing
	We malloc ex and give the stats of 0 (I don't understand why yet tho)

*/

int	main(int argc, char **argv, char **env)
{
	t_exec		*ex;
	t_parsing 	*parse;
	(void)argv;

	ex = ft_calloc(1, sizeof(t_exec));
	ex->status = 0;
	if (argc > 1)
	{
		fprintf(stderr, "Why U put params?!?!\n");
		free(ex);
		return (1);
	}
	print_logo(env);
	ex->new_env = copy_strarr(env);
	while (1)
	{
		ex->prompt = set_prompt(ex->new_env);
		ex->line = readline(ex->prompt);
		free(ex->prompt);
		if (ex->line == NULL)
		{
			free(ex->line);
			free_strrarr(ex->new_env);
			return (0);
		}
		if (*ex->line)
		{
			add_history(ex->line);
			parse = start_parse(ex->line, ex->status);
			if (parse == NULL)
			{
				free(ex->line);
				continue;
			}
			parse->ex = ex; 
			parse->tkns_list = parse->tkns_list->start;
			ex->s_line = parse->tkns_list->vector_cmd;
			if (ex->s_line[0] == NULL)// pas certain de savoir  à quoi ça sert ce if là
			{
				free(ex->line);
				free_strrarr(ex->s_line);
				continue ;
			}
			calling_the_execs_shell(ex->s_line, &ex->new_env, parse);
			wait_for_pids(parse); 
			free_strrarr(ex->s_line);
		}
		free(ex->line);
	}
	free_strrarr(ex->path);
	// free(ex->prompt);
	free (ex); // valider comment bien free toute la structure
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