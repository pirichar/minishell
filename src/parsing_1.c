
#include "../include/minishell.h"

int	start_parse(char *line, char *env[])
{
	t_parsing	*parse_list;
	int			i;

	i = 0;
	parse_list = malloc(sizeof(t_parsing));
	if (line)
	{
		parse_list->cmds = malloc(13 * sizeof(char *));
		parse_list->cmds[0] = calloc(8, sizeof(char));
		parse_list->cmds[0] = "Makefile";
		parse_list->cmds[1] = calloc(2, sizeof(char));
		parse_list->cmds[1] = "<<";
		parse_list->cmds[2] = calloc(6, sizeof(char));
		parse_list->cmds[2] = "\"echo\"";
		parse_list->cmds[3] = calloc(2, sizeof(char));
		parse_list->cmds[3] = "-n";
		parse_list->cmds[4] = calloc(8, sizeof(char));
		parse_list->cmds[4] = "allo toi";
		parse_list->cmds[5] = calloc(2, sizeof(char));
		parse_list->cmds[5] = "ca";
		parse_list->cmds[6] = calloc(4, sizeof(char));
		parse_list->cmds[6] = "$PWD";
		parse_list->cmds[7] = calloc(47, sizeof(char));
		parse_list->cmds[7] = "\"lui                             est le best\""; // il faut quand tu split, il y est un flag pour les quotes, question que je sache si il y a des quotes ou non ds le token, si oui, faut il les enlever oui ou non
		parse_list->cmds[8] = calloc(2, sizeof(char));
		parse_list->cmds[8] = "&&";
		parse_list->cmds[9] = calloc(2, sizeof(char));
		parse_list->cmds[9] = "||";
		parse_list->cmds[10] = calloc(2, sizeof(char));
		parse_list->cmds[10] = ">>";
		parse_list->cmds[11] = calloc(7, sizeof(char));
		parse_list->cmds[11] = "outfile";
		parse_list->cmds[12] = NULL;
	}
	// while (parse_list->cmds[i])
	// {
	// 	printf("token %d = %s\n", i, parse_list->cmds[i]);
	// 	i++;
	// }
	put_on_the_props(parse_list, env);
	return (0);
}

int	put_on_the_props(t_parsing *parse_list, char *env[])
{
	int	tks_cnt;
	int	i;
	int	j;

	j = 0;
	i = 0;
	tks_cnt = cnt_tokens(parse_list->cmds);
	parse_list->commands = malloc(sizeof(t_parsing));
	parse_list->commands->start = parse_list->commands;
	while (tks_cnt > i)
	{
		parse_list->commands->cmd = calloc(ft_strlen(parse_list->cmds[i]), sizeof(char));
		while (parse_list->cmds[i][j])
		{
			parse_list->commands->cmd[j] = parse_list->cmds[i][j];
			if (parse_list->commands->cmd[j] == '"')
				parse_list->commands->quotes = true;
			else
				parse_list->commands->quotes = false;
			j++;
		}
		check_tokens(parse_list->commands->cmd, parse_list, env);
		j = 0;
		i++;
		parse_list->commands->next = malloc(sizeof(t_parsing));
		(parse_list->commands->next)->start = parse_list->commands->start;
		parse_list->commands = parse_list->commands->next;
	}
	parse_list->commands->next = NULL;
	parse_list->commands = parse_list->commands->start;
	return (0);
}

int	check_tokens(char *cmd, t_parsing *parse_list, char *env[])
{
	int	i;

	i = 0;
	while (ft_strncmp(*env, "PATH=", 5))
		env++;
	if (parse_list->commands->quotes == true)
	{
		parse_list->commands->cmd = ft_strtrim(parse_list->commands->cmd, "\"");
		cmd = ft_strtrim(cmd, "\"");
	}
	if (check_exe(cmd, env) == 0)
		parse_list->commands->flags = 0;
	else if (!ft_strncmp(cmd, "<<\0", 3) || (!ft_strncmp(cmd, ">>\0", 3)))
		parse_list->commands->flags = 1;
	else if (!ft_strncmp(cmd, "-", 1))
		parse_list->commands->flags = 2;
	else if (!ft_strncmp(cmd, "&&\0", 3))
		parse_list->commands->flags = 3;
	else if (!ft_strncmp(cmd, "||\0", 3))
		parse_list->commands->flags = 4;
	else if (!ft_strncmp(cmd, "$", 1))
		parse_list->commands->flags = 5;
	else
		parse_list->commands->flags = 6;
	// if (parse_list->commands->quotes == true)
	// 	printf("with quotes = True %d  ", parse_list->commands->quotes);
	// printf("token : %s = %d\n", parse_list->commands->cmd, parse_list->commands->flags);
	still_parsing(parse_list);
	return (0);
}

int	still_parsing(t_parsing *parse_list)
{
	(void)parse_list;
	return (0);
}

int	check_exe(char *cmd, char *env[])
{
	char	**path_split;
	int		i;
	int		si_o_no;
	char	*cmd_temp;
	char	*temp_path;

	i = 0;
	si_o_no = -1;
	path_split = ft_split(*env + 5, ':');
	cmd_temp = ft_strjoin("/", cmd);
	while (si_o_no == -1 && path_split[i])
	{
		temp_path = ft_strjoin(path_split[i], cmd_temp);
		si_o_no = access(temp_path, X_OK);
		if (si_o_no == -1)
		{
			free(temp_path);
			free(path_split[i]);
		}
		i++;
	}
	if (si_o_no != -1)
	{
		free(path_split[i]);
		free(temp_path);
	}
	free(cmd_temp);
	return (si_o_no);
}

int	cnt_tokens(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}

void	free_them(t_parsing *parse_list)
{
	while (parse_list->commands->next != NULL)
	{
		free(parse_list->commands);
		parse_list->commands = parse_list->commands->next;
	}
	free(parse_list->commands);
}
// 	i = 0;
// 	nb_tokens(&parse_list, line);
// 	init_parse(&parse_list);
// 	while (line[i] && line)
// 	{
// 		if (line[i] == '"')
// 		{
// 			parse_list.doub_quotes++;
// 			i++;
// 		}
// 		if (line[i] == 47)
// 		{
// 			parse_list.sing_quotes++;
// 			i++;
// 		}
// 		if (line[i] == ' ')
// 		{
// 			i++;
// 			line = tokenization(line, i, &parse_list);
// 		}
// 		i++;
// 	}
// 	line = tokenization(line, i, &parse_list);
// 	return (0);
// }

// void	init_parse(t_parsing *parse_list)
// {
// 	parse_list->nb_quote = 0;
// 	parse_list->sing_quotes = 0;
// 	parse_list->doub_quotes = 0;
// 	parse_list->nb_cmd = -1;
// 	parse_list->cmds = malloc(parse_list->nb_tokens * sizeof(char *));
// }

// char	*tokenization(char *line, int i, t_parsing *parse_list)
// {
// 	int	j;
// 	int	k;

// 	j = 0;
// 	k = 0;
// 	parse_list->nb_cmd++;
// 	parse_list->cmds[parse_list->nb_cmd] = malloc(i * sizeof(char));
// 	while (i > j)
// 	{
// 		parse_list->cmds[parse_list->nb_cmd][k] = *line;
// 		line++;
// 		i--;
// 		k++;
// 	}
// 	printf("l = %s\n", parse_list->cmds[parse_list->nb_cmd]);
// 	return (line);
// }

// int	nb_tokens(t_parsing *parse_list, char *line)
// {
// 	int	i;
// 	int	quotes_pair;

// 	parse_list->nb_tokens = 0;
// 	i = 0;
// 	quotes_pair = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == ' ')
// 			parse_list->nb_tokens++;
// 		if (line[i] == 47 || line[i] == '"')
// 		{
// 			if (quotes_pair % 2 == 0)
// 				i++;
// 			quotes_pair++;
// 		}
// 		i++;
// 	}
// 	parse_list->nb_tokens++;
// 	return (0);
// }