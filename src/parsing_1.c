
#include "../include/minishell.h"

int	start_parse(char *line)
{
	t_parsing	parse_list;
	int			i;

	i = 0;
	nb_tokens(&parse_list, line);
	init_parse(&parse_list);
	while (line[i] && line)
	{
		if (line[i] == '"')
		{
			parse_list.doub_quotes++;
			i++;
		}
		if (line[i] == 47)
		{
			parse_list.sing_quotes++;
			i++;
		}
		if (line[i] == ' ')
		{
			i++;
			line = tokenization(line, i, &parse_list);
		}
		i++;
	}
	line = tokenization(line, i, &parse_list);
	return (0);
}

void	init_parse(t_parsing *parse_list)
{
	parse_list->nb_quote = 0;
	parse_list->sing_quotes = 0;
	parse_list->doub_quotes = 0;
	parse_list->nb_cmd = -1;
	parse_list->cmds = malloc(parse_list->nb_tokens * sizeof(char *));
}

char	*tokenization(char *line, int i, t_parsing *parse_list)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	parse_list->nb_cmd++;
	parse_list->cmds[parse_list->nb_cmd] = malloc(i * sizeof(char));
	while (i > j)
	{
		parse_list->cmds[parse_list->nb_cmd][k] = *line;
		line++;
		i--;
		k++;
	}
	printf("l = %s\n", parse_list->cmds[parse_list->nb_cmd]);
	return (line);
}

int	nb_tokens(t_parsing *parse_list, char *line)
{
	int	i;
	int	quotes_pair;

	parse_list->nb_tokens = 0;
	i = 0;
	quotes_pair = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			parse_list->nb_tokens++;
		if (line[i] == 47 || line[i] == '"')
		{
			if (quotes_pair % 2 == 0)
				i++;
			quotes_pair++;
		}
		i++;
	}
	parse_list->nb_tokens++;
	return (0);
}