#include "../include/minishell.h"

int	start_parse(char *line, char *env[])
{
	t_parsing	*parse_list;
	int			i;

	i = 0;
	parse_list = malloc(sizeof(t_parsing));
	if (line)
	{
		parse_list->tkns_array = malloc(13 * sizeof(char *));
		parse_list->tkns_array[0] = calloc(9, sizeof(char));
		parse_list->tkns_array[0] = "Makefile	";
		parse_list->tkns_array[1] = calloc(2, sizeof(char));
		parse_list->tkns_array[1] = "<<";
		parse_list->tkns_array[2] = calloc(6, sizeof(char));
		parse_list->tkns_array[2] = "\'echo\'";
		parse_list->tkns_array[3] = calloc(2, sizeof(char));
		parse_list->tkns_array[3] = "\"'-n'\"";
		parse_list->tkns_array[4] = calloc(10, sizeof(char));
		parse_list->tkns_array[4] = "'allo $PWD toi'";
		parse_list->tkns_array[5] = calloc(8, sizeof(char));
		parse_list->tkns_array[5] = "/bin/cat";
		parse_list->tkns_array[6] = calloc(4, sizeof(char));
		parse_list->tkns_array[6] = "$PWD";
		parse_list->tkns_array[7] = calloc(48, sizeof(char));
		parse_list->tkns_array[7] = "\"lui          $LANG               est le best\""; // il faut quand tu split, il y est un flag pour les quotes, question que je sache si il y a des quotes ou non ds le token, si oui, faut il les enlever oui ou non
		parse_list->tkns_array[8] = calloc(2, sizeof(char));
		parse_list->tkns_array[8] = "&&";
		parse_list->tkns_array[9] = calloc(2, sizeof(char));
		parse_list->tkns_array[9] = "||";
		parse_list->tkns_array[10] = calloc(2, sizeof(char));
		parse_list->tkns_array[10] = ">>";
		parse_list->tkns_array[11] = calloc(7, sizeof(char));
		parse_list->tkns_array[11] = "outfile";
		parse_list->tkns_array[12] = NULL;
	}
	// while (parse_list->tkns_array[i])
	// {
	// 	printf("token %d = %s\n", i, parse_list->tkns_array[i]);
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
	tks_cnt = cnt_tokens(parse_list->tkns_array);
	parse_list->tkns_list = malloc(sizeof(t_parsing));
	parse_list->tkns_list->start = parse_list->tkns_list;
	while (tks_cnt > i)
	{
		parse_list->tkns_list->tkn = calloc(ft_strlen(parse_list->tkns_array[i]) + 1, sizeof(char));
		while (parse_list->tkns_array[i][j])
		{
			parse_list->tkns_list->tkn[j] = parse_list->tkns_array[i][j];
			if (parse_list->tkns_list->tkn[0] == '"' )
				parse_list->tkns_list->db_quotes = true;
			else
				parse_list->tkns_list->db_quotes = false;
			if (parse_list->tkns_list->tkn[0] == '\'')
				parse_list->tkns_list->sing_quotes = true;
			else
				parse_list->tkns_list->sing_quotes = false;
			j++;
		}
		check_tokens(parse_list->tkns_list->tkn, parse_list, env);
		j = 0;
		i++;
		parse_list->tkns_list->next = malloc(sizeof(t_parsing));
		(parse_list->tkns_list->next)->start = parse_list->tkns_list->start;
		parse_list->tkns_list = parse_list->tkns_list->next;
	}
	parse_list->tkns_list->next = NULL;
	parse_list->tkns_list = parse_list->tkns_list->start;
	return (0);
}

int	check_tokens(char *cmd, t_parsing *parse_list, char *env[])
{
	int		i;
	char	**temp;

	i = 0;
	temp = env;
	while (ft_strncmp(*temp, "PATH=", 5))
		temp++;
	if (parse_list->tkns_list->db_quotes == true)
	{
		parse_list->tkns_list->tkn = ft_strtrim(parse_list->tkns_list->tkn, "\"");
		cmd = ft_strtrim(cmd, "\"");
	}
	if (parse_list->tkns_list->sing_quotes == true)
	{
		parse_list->tkns_list->tkn = ft_strtrim(parse_list->tkns_list->tkn, "'");
		cmd = ft_strtrim(cmd, "'");
	}
	if (check_exe(cmd, temp) == 0)
		parse_list->tkns_list->flags = 0;
	else if (!ft_strncmp(cmd, "<<\0", 3) || (!ft_strncmp(cmd, ">>\0", 3)))
		parse_list->tkns_list->flags = 1;
	else if (!ft_strncmp(cmd, "-", 1))
		parse_list->tkns_list->flags = 2;
	else if (!ft_strncmp(cmd, "&&\0", 3))
		parse_list->tkns_list->flags = 3;
	else if (!ft_strncmp(cmd, "||\0", 3))
		parse_list->tkns_list->flags = 4;
	else if (!ft_strncmp(cmd, "$", 1))
		parse_list->tkns_list->flags = 5;
	else
		parse_list->tkns_list->flags = 6;
	if (parse_list->tkns_list->db_quotes == true || parse_list->tkns_list->sing_quotes == true)
		printf("with quotes = True ");
	printf("token : %s = %d cmmmmmmd %s\n", parse_list->tkns_list->tkn, parse_list->tkns_list->flags, cmd);
	check_var(parse_list, cmd, env);
	return (0);
}

int	check_var(t_parsing *parse_list, char *cmd, char *env[])
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	j = 0;
	var = calloc(ft_strlen(cmd) , sizeof(char));
	if (parse_list->tkns_list->flags == 5)
	{
		var = get_var(parse_list, cmd, env);
		free(var);
		return (0);
	}
	if (parse_list->tkns_list->db_quotes == true)
	{
		while (cmd[i])
		{
			if (cmd[i] == '$')
			{
				while ((cmd[i]) && (cmd[i] != 32 || cmd[i] != '\0'))
				{
					var[j] = cmd[i];
					i++;
					j++;
					if (cmd[i] == ' ')
					{
						var[j] = '\0';
						break ;
					}
				}
				if (j == 1)
				{
					free(var);
				}
				else
				{
					var = get_var(parse_list, var, env);
					printf("var %s\n", var);
					break ;
				}
			}
			i++;
		}
	}
	return (0);
}

char	*get_var(t_parsing *parse_list, char *var, char *env[])
{
	int		len;
	int		i;
	char	*var_name;

	(void)parse_list;
	i = 0;
	len = ft_strlen(var);
	while (env[i])
	{
		if (!ft_strncmp(env[i], var + 1, len - 1))
		{
			var_name = calloc(ft_strlen(env[i]), sizeof(char));
			ft_strlcpy(var_name, env[i] + len, ft_strlen(env[i]) - len + 1);
		}
		i++;
	}
	return (var_name);
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
	si_o_no = access(cmd, X_OK);
	if (si_o_no != -1)
		return (si_o_no);
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
	while (parse_list->tkns_list->next != NULL)
	{
		free(parse_list->tkns_list);
		parse_list->tkns_list = parse_list->tkns_list->next;
	}
	free(parse_list->tkns_list);
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
// 	parse_list->tkns_array = malloc(parse_list->nb_tokens * sizeof(char *));
// }

// char	*tokenization(char *line, int i, t_parsing *parse_list)
// {
// 	int	j;
// 	int	k;

// 	j = 0;
// 	k = 0;
// 	parse_list->nb_cmd++;
// 	parse_list->tkns_array[parse_list->nb_cmd] = malloc(i * sizeof(char));
// 	while (i > j)
// 	{
// 		parse_list->tkns_array[parse_list->nb_cmd][k] = *line;
// 		line++;
// 		i--;
// 		k++;
// 	}
// 	printf("l = %s\n", parse_list->tkns_array[parse_list->nb_cmd]);
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