#include "../include/minishell.h"

/*
	This function basically printf stuff
	It first look for -n -nnn and multiples -n
	Then once it filtered all the -n
	After that it set check_nl to false
	this way it does not look for flags
	to parse but print them out instead
*/
void	mini_echo(char **s_line, t_parsing *parse)
{
	int		i;

	i = 1;
	parse->with_nl = true;
	parse->check_nl = true;
	parse->b_in = true;
	// int y = 0;
	// while (s_line[y])
	// {
	// 	printf("I am inside s_line: %s\n", s_line[y]);
	// 	y++;
	// }
	while (s_line[i] != NULL)
	{
		parse_echo(s_line, &parse->check_nl, &parse->with_nl, i);
		if (s_line[i] == NULL)
			return ;
		parse->check_nl = false;
		if (s_line[i + 1])
			dprintf(parse->outfile, "%s ", s_line[i]);
		else
			dprintf(parse->outfile, "%s", s_line[i]);
		i++;
	}
	if (parse->with_nl)
		dprintf(parse->outfile, "\n");
}

//s'assurer que dans la version officielle echo "-n" 
// fonctionne aussi mais pas echo " -n"

bool	check_only_n(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

void	parse_echo(char **s_line, bool *check_nl, bool *with_nl, int i)
{
	while (s_line[i] && ft_strncmp(s_line[i], "-n", 2) == 0
		&& (*check_nl))
	{
		if (check_only_n(s_line[i]))
			(*with_nl) = false;
		else
			break ;
		i++;
	}
}
