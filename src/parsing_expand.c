
#include "../include/minishell.h"

char *check_env(char *s, t_parsing *parse_list, int start)
{
	char *new;
	bool found;
	int x;
	int y;
	int i;
	int search;


	found = false;
	x = 0;
	y = 0;
	i = 0;
	new = ft_calloc(1000, sizeof(char));
	while (i < start - 1)
	{
		new[i] = s[y];
		y++;
		i++;
	}
	while (ex->new_env[x])
	{
		search = start;
		y = 0;
		while(ex->new_env[x][y] && s[search] != '\0' && ft_isspace(s[search]) == false)
		{
			if(s[search] != ex->new_env[x][y])
				break ;
			if ((ft_isspace(s[search + 1]) == true || s[search + 1] == '\0') && ex->new_env[x][y + 1] == '=')
			{
				found = true;
				break ;
			}
			y++;
			search++;
		}
		if (found == false)
			x++;
		else
			break ;
	}
	if (found == true)
	{
		y += 2;
		int quote;
		quote = y;
		while (ex->new_env[x][y] != '\0')
		{
			new[i] = ex->new_env[x][y];
			y++;
			i++;
		}
		parse_list->quote_end = parse_list->quote_end + y - (quote * 2);
		while (s[++search])
		{
			new[i] = s[search];
			i++;
		}
		new[i] = '\0';
		parse_list->tkns_list->dollar_sign = true;
		return (new);
	}
	else
		return(s);
	}

char *expend_var(char *cmd, t_parsing *parse_list, int i)
{
	parse_list->tkns_list->dollar_sign = false;
	while (cmd[i] && parse_list->tkns_list->dollar_sign == false)
	{
		if (cmd[i] == '$')
			cmd = check_env(cmd, parse_list, i + 1);
		i++;
	}
	return (cmd);
}