
#include "../include/minishell.h"

int	start_parse(char *line)
{
	t_parsing	*parse_list;
	int			i;

	i = 0;
	parse_list = malloc(sizeof(t_parsing));
	if (line)
	{
		parse_list->cmds = malloc(12 * sizeof(char *));
		parse_list->cmds[0] = malloc(8 * sizeof(char));
		parse_list->cmds[0] = "Makefile";
		parse_list->cmds[1] = malloc(2 * sizeof(char));
		parse_list->cmds[1] = "<<";
		parse_list->cmds[2] = malloc(4 * sizeof(char));
		parse_list->cmds[2] = "echo";
		parse_list->cmds[3] = malloc(2 * sizeof(char));
		parse_list->cmds[3] = "-n";
		parse_list->cmds[4] = malloc(8 * sizeof(char));
		parse_list->cmds[4] = "allo toi";
		parse_list->cmds[5] = malloc(2 * sizeof(char));
		parse_list->cmds[5] = "ca";
		parse_list->cmds[6] = malloc(47 * sizeof(char));
		parse_list->cmds[6] = "lui                             est le best";
		parse_list->cmds[7] = malloc(2 * sizeof(char));
		parse_list->cmds[7] = "&&";
		parse_list->cmds[8] = malloc(2 * sizeof(char));
		parse_list->cmds[8] = "||";
		parse_list->cmds[9] = malloc(2 * sizeof(char));
		parse_list->cmds[9] = ">>";
		parse_list->cmds[10] = malloc(7 * sizeof(char));
		parse_list->cmds[10] = "outfile";
		parse_list->cmds[11] = NULL;
	}
	while (parse_list->cmds[i])
	{
		printf("token %d = %s\n", i, parse_list->cmds[i]);
		i++;
	}
	put_on_the_props(parse_list);
	return (1);
}

int	put_on_the_props(t_parsing *parse_list)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	j = 0;
	i = cnt_tokens(parse_list->cmds);
	parse_list->commands = malloc(sizeof(t_parsing));
	parse_list->commands->start = parse_list->commands;
	while (i > j)
	{
		parse_list->commands->cmd = malloc(ft_strlen(parse_list->cmds[j]));
		while (parse_list->cmds[j][k])
		{
			parse_list->commands->cmd[k] = parse_list->cmds[j][k];
			k++;
		}
		check_flags(parse_list);
		k = 0;
		j++;
		parse_list->commands->next = malloc(sizeof(t_parsing));
		(parse_list->commands->next)->start = parse_list->commands->start;
		parse_list->commands = parse_list->commands->next;
	}
	parse_list->commands->next = NULL;
	parse_list->commands = parse_list->commands->start;
	while (parse_list->commands->next != NULL)
	{
		printf("tokenasdjagsj = %s\n", parse_list->commands->cmd);
		parse_list->commands = parse_list->commands->next;
	}
	return (0);
}

int	check_flags(t_parsing *parse_list)
{
	if (parse_list)
		return (1);
	return (0);
}

int	cnt_tokens(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
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