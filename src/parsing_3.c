#include "../include/minishell.h"

void	helper_get_arg(t_parsing	*parse_list, int y, char ***tab_tab)
{
	int	i;
	int	z;

	i = 0;
	z = 0;
	while (parse_list->tkns_list->tok_type != PIPE)
	{
		z = 0;
		tab_tab[i][y] = ft_calloc(ft_strlen
				(parse_list->tkns_list->data), sizeof(char));
		while (parse_list->tkns_list->data[z] != '\0')
		{
			tab_tab[i][y][z] = parse_list->tkns_list->data[z];
			z++;
		}
		y++;
		if (parse_list->tkns_list->next != NULL)
			parse_list->tkns_list = parse_list->tkns_list->next;
		else
			break ;
	}
}

char	***get_argarray(t_parsing *parse_list)
{
	char	***tab_tab;
	int		i;
	int		y;

	i = 0;
	tab_tab = ft_calloc(parse_list->nb_of_pipes, sizeof(char **));
	while (parse_list->tkns_list != NULL)
	{
		y = 0;
		if (parse_list->tkns_list->tok_type
			== ARG && i < parse_list->nb_of_pipes)
		{
			tab_tab[i] = prep_tab(parse_list->tkns_list);
			helper_get_arg(parse_list, y, tab_tab);
			i++;
		}
		else if (parse_list->tkns_list->next != NULL)
			parse_list->tkns_list = parse_list->tkns_list->next;
		else
			break ;
	}
	return (tab_tab);
}

char	*search_env(char *s, int search, t_parsing *p_list)
{
	p_list->p_x = 0;
	p_list->p_start = search;
	while (ex->new_env[p_list->p_x])
	{
		p_list->p_y = 0;
		search = p_list->p_start;
		while (ex->new_env[p_list->p_x][p_list->p_y] && s[search] != '\0'
			&& ft_isspace(s[search]) == false)
		{
			if (s[search] != ex->new_env[p_list->p_x][p_list->p_y])
				break ;
			if ((ft_isspace(s[search + 1]) == true || s[search + 1] == '\0'
					|| s[search + 1] == p_list->quote_type)
				&& ex->new_env[p_list->p_x][p_list->p_y + 1] == '=')
			{
				p_list->index += p_list->p_y + 2;
				p_list->to_skip = p_list->p_y + 2;
				return (ex->new_env[p_list->p_x]);
			}
			p_list->p_y++;
			search++;
		}
		p_list->p_x++;
	}
	return (NULL);
}

char	*joining(char *s1, char *s2, t_parsing *parse_list)
{
	char	*str;
	int		j;
	int		i;

	i = 0;
	j = parse_list->to_skip;
	if (!s2)
		return (s1);
	if (!s1)
		return (s2);
	str = ft_calloc(MAX_INPUT, sizeof(char));
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	parse_list->new_i = i;
	return (str);
}

char	*expand_var(char *line, t_parsing *p_l)
{
	p_l->p_new = ft_calloc(MAX_INPUT, sizeof(char));
	while (line[p_l->index])
	{
		if (line[p_l->index] == '$')
		{
			if (p_l->quotes == true && (p_l->index
					< p_l->quote_start || p_l->index > p_l->quote_end))
				p_l->p_new = joining(p_l->p_new, search_env(line,
							p_l->index + 1, p_l), *&p_l);
			else if (p_l->quotes == true
				&& p_l->quote_type == 34 && (p_l->index > p_l->quote_start
					|| p_l->index < p_l->quote_end))
				p_l->p_new = joining(p_l->p_new, search_env(line,
							p_l->index + 1, p_l), *&p_l);
			else if (p_l->quotes == false)
				p_l->p_new = joining(p_l->p_new, search_env(line,
							p_l->index + 1, p_l), *&p_l);
		}
		if ((p_l->index == p_l->quote_end)
			&& (line[p_l->index] == p_l->quote_type))
			p_l->quote_end = p_l->new_i;
		p_l->p_new [p_l->new_i++] = line[p_l->index++];
	}
	return (p_l->p_new);
}