#include "../include/minishell.h"

/*
	This function basically printf stuff
	It first look for -n -nnn and multiples -n
	Then once it filtered all the -n
	After that it set check_nl to false
	this way it does not look for flags
	to parse but print them out instead
*/
void	mini_echo(char **s_line, bool *b_in)
{
	int		i;
	int		j;
	bool	with_nl;
	bool	check_nl;

	i = 1;
	j = 1;
	with_nl = true;
	check_nl = true;
	*b_in = true;
	while (s_line[i])
	{
		parse_echo(s_line, &check_nl, &with_nl, &i);
		if (s_line[i] == NULL)
			return ;
		check_nl = false;
		if (s_line[i][0] == '*' && s_line[i][1] == 0)
		{
			mom_i_am_a_star_p();
			i++;
			continue;
		}
		if (s_line[i + 1])
			printf("%s ", s_line[i]);
		else
			printf("%s", s_line[i]);
		i++;
	}
	if (with_nl)
		printf("\n");
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

void	parse_echo(char **s_line, bool *check_nl, bool *with_nl, int *i)
{
	while (s_line[*(i)] && ft_strncmp(s_line[*(i)], "-n", 2) == 0
		&& (*check_nl))
	{
		if (check_only_n(s_line[*(i)]))
			(*with_nl) = false;
		else
			break ;
		(*i)++;
	}
}