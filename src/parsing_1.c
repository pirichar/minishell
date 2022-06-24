#include "../include/minishell.h"

int	start_parse(char *line)
{
	int			i;
	t_parsing	*parse_list;

	i = 0;
	parse_list = malloc(sizeof(t_parsing));
	parse_list->tkns_array = split(line);
	if (parse_list->tkns_array == NULL)
		return (0);
	if (parse_list->tkns_array)
		put_on_the_props(parse_list);
	return (0);
}

int	put_on_the_props(t_parsing *parse_list)
{
	parse_list->tkns_list = malloc(sizeof(t_parsing));
	parse_list->tkns_list->prev = NULL;
	parse_list->tkns_list->start = parse_list->tkns_list;
	assign_the_list(parse_list);
	parse_list->tkns_list->next = NULL;
	parse_list->tkns_list->tkn = NULL;
	parse_list->tkns_list = parse_list->tkns_list->start;
	check_tokens(parse_list);
	return (0);
}

int	assign_the_list(t_parsing *parse_list)
{
	int	tks_cnt;
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	tks_cnt = cnt_tokens(parse_list->tkns_array);
	while (tks_cnt > i)
	{
		parse_list->tkns_list->argv_pos = i;
		parse_list->tkns_list->tkn = calloc(ft_strlen(parse_list->tkns_array[i])
				+ 1, sizeof(char));
		while (parse_list->tkns_array[i][j])
		{
			if (parse_list->tkns_array[i][j] == '&')
			{
				if (k != 0)
					{
						printf("token = %s\n", parse_list->tkns_list->tkn);
						parse_list->tkns_list->next = malloc(sizeof(t_parsing));
						parse_list->tkns_list->next->prev = parse_list->tkns_list;
							(parse_list->tkns_list->next)->start = parse_list->tkns_list->start;
						parse_list->tkns_list = parse_list->tkns_list->next;
						parse_list->tkns_list->tkn = calloc(ft_strlen(parse_list->tkns_array[i])
							+ 1, sizeof(char));
						k = 0;
					}
				if (parse_list->tkns_array[i][j + 1] == '&')
				{
					
					{
						parse_list->tkns_list->tkn[k] = parse_list->tkns_array[i][j];
						j++;
						k++;
						parse_list->tkns_list->tkn[k] = parse_list->tkns_array[i][j];
						k++;
						j++;
						parse_list->tkns_list->tkn[k] = '\0';
						printf("token = %s\n", parse_list->tkns_list->tkn);
						parse_list->tkns_list->next = malloc(sizeof(t_parsing));
						parse_list->tkns_list->next->prev = parse_list->tkns_list;
						(parse_list->tkns_list->next)->start = parse_list->tkns_list->start;
						parse_list->tkns_list = parse_list->tkns_list->next;
						parse_list->tkns_list->tkn = calloc(ft_strlen(parse_list->tkns_array[i])
						+ 1, sizeof(char));
						k = 0;
					}
				}
			}
			if (parse_list->tkns_array[i][j] == '\0')
				break ;
			else
			{
				parse_list->tkns_list->tkn[k] = parse_list->tkns_array[i][j];
				j++;
				k++;
			}
		}
		parse_list->tkns_list->tkn[k] = '\0';
		if (parse_list->tkns_list->tkn == NULL)
			parse_list->tkns_list = parse_list->tkns_list->prev;
		printf("token = %s\n", parse_list->tkns_list->tkn);
		j = 0;
		k = 0;
		j = 0;
		i++;
		parse_list->tkns_list->next = malloc(sizeof(t_parsing));
		parse_list->tkns_list->next->prev = parse_list->tkns_list;
		(parse_list->tkns_list->next)->start = parse_list->tkns_list->start;
		parse_list->tkns_list = parse_list->tkns_list->next;
	}
	return (0);
}

int	check_tokens(t_parsing *parse_list)
{
	int	i;

	i = 0;
	parse_list->tkns_list = parse_list->tkns_list->start;
	while (parse_list->tkns_list->next != NULL)
	{
		if ((!ft_strncmp(parse_list->tkns_list->tkn, "\\", 1)))
			printf("do the wait for input or do the error ig, idk i dont even work here\n");
		else if (parse_list->tkns_list->argv_pos == 0)
			argv0(parse_list);
		else if ((!ft_strncmp(parse_list->tkns_list->tkn, "&&\0", 3)))
			// put_ampers_props(parse_list);
			printf("hahaha\n");
		else if ((!ft_strncmp(parse_list->tkns_list->tkn, "||\0", 3)))
			printf("do the pipes(parse_list)\n");
		parse_list->tkns_list = parse_list->tkns_list->next;
	}
	return (0);
}

int	argv0(t_parsing *parse_list)
{
	if (!ft_strncmp(parse_list->tkns_list->tkn, "<\0", 2))
		put_redirect_props(parse_list);
	else if (!ft_strncmp(parse_list->tkns_list->tkn, "&", 1)
		|| (!ft_strncmp(parse_list->tkns_list->tkn, "|", 1)))
		printf("DunderShell: syntax error near unexpected token `%.2s'\n",
			parse_list->tkns_list->tkn);
	else
	{
		parse_list->tkns_list->flags = 0;
		printf("do_the_exe_baby(parse_list) tkn %s, argv pos %d, flags %d\n",
			parse_list->tkns_list->tkn, parse_list->tkns_list->argv_pos,
			parse_list->tkns_list->flags);
	}
	return (0);
}

int	put_ampers_props(t_parsing *parse_list)
{
	parse_list->tkns_list->flags = 3;
	if (parse_list->tkns_list->next != NULL)
		parse_list->tkns_list->next->flags = 0;
	return (0);
}

int	put_redirect_props(t_parsing *parse_list)
{
	if (parse_list->tkns_list->next->tkn != NULL)
	{
		parse_list->tkns_list->flags = 1;
		parse_list->tkns_list->next->flags = 7;
		parse_list->tkns_list = parse_list->tkns_list->next;
	}
	else
	{
		parse_list->tkns_list->flags = 69;
		printf("DunderShell: syntax error near unexpected token `newline' \n");
		return (1);
	}
	if (parse_list->tkns_list->next->tkn != NULL)
	{
		parse_list->tkns_list->next->flags = 0;
		parse_list->tkns_list = parse_list->tkns_list->next;
	}
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


// int	check_var(t_parsing *parse_list, char *cmd, char *env[])
// {
// 	int		i;
// 	int		j;
// 	char	*var;

// 	i = 0;
// 	j = 0;
// 	var = calloc(ft_strlen(cmd) , sizeof(char));
// 	if (parse_list->tkns_list->flags == 5)
// 	{
// 		var = get_var(parse_list, cmd, env);
// 		printf("var %s\n", var);
// 		free(var);
// 		return (0);
// 	}
// 	if (parse_list->tkns_list->db_quotes == true)
// 	{
// 		while (cmd[i])
// 		{
// 			if (cmd[i] == '$')
// 			{
// 				while ((cmd[i]) && (cmd[i] != 32 || cmd[i] != '\0'))
// 				{
// 					var[j] = cmd[i];
// 					i++;
// 					j++;
// 					if (cmd[i] == ' ')
// 					{
// 						var[j] = '\0';
// 						break ;
// 					}
// 				}
// 				if (j == 1)
// 				{
// 					free(var);
// 				}
// 				else
// 				{
// 					var = get_var(parse_list, var, env);
// 					printf("var %s\n", var);
// 					break ;
// 				}
// 			}
// 			i++;
// 		}
// 	}
// 	return (0);
// }

// char	*get_var(t_parsing *parse_list, char *var, char *env[])
// {
// 	int		len;
// 	int		i;
// 	char	*var_name;

// 	(void)parse_list;
// 	i = 0;
// 	len = ft_strlen(var);
// 	while (env[i])
// 	{
// 		if (!ft_strncmp(env[i], var + 1, len - 1))
// 		{
// 			var_name = calloc(ft_strlen(env[i]), sizeof(char));
// 			ft_strlcpy(var_name, env[i] + len, ft_strlen(env[i]) - len + 1);
// 		}
// 		i++;
// 	}
// 	return (var_name);
// }

// int	check_exe(char *cmd, char *env[])
// {
// 	char	**path_split;
// 	int		i;
// 	int		si_o_no;
// 	char	*cmd_temp;
// 	char	*temp_path;

// 	i = 0;
// 	si_o_no = -1;
// 	si_o_no = access(cmd, X_OK);
// 	if (si_o_no != -1)
// 		return (si_o_no);
// 	path_split = ft_split(*env + 5, ':');
// 	cmd_temp = ft_strjoin("/", cmd);
// 	while (si_o_no == -1 && path_split[i])
// 	{
// 		temp_path = ft_strjoin(path_split[i], cmd_temp);
// 		si_o_no = access(temp_path, X_OK);
// 		if (si_o_no == -1)
// 		{
// 			free(temp_path);
// 			free(path_split[i]);
// 		}
// 		i++;
// 	}
// 	if (si_o_no != -1)
// 	{
// 		free(path_split[i]);
// 		free(temp_path);
// 	}
// 	free(cmd_temp);
// 	return (si_o_no);
// }

// void	free_them(t_parsing *parse_list)
// {
// 	while (parse_list->tkns_list->next != NULL)
// 	{
// 		free(parse_list->tkns_list);
// 		parse_list->tkns_list = parse_list->tkns_list->next;
// 	}
// 	free(parse_list->tkns_list);
// }
