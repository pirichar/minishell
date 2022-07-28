#include "../include/minishell.h"

int	check_metachar(t_parsing *parse_list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (parse_list->tkns_array[i])
	{
		while (parse_list->tkns_array[i][j])
		{
			if (ft_strchr("<|>", parse_list->tkns_array[i][0]))
			{
				if (parse_list->tkns_array[i][0] == '<')
				{
					if (parse_list->tkns_array[i][1] == '<')
					{
						if (check_file_and_delim_name(parse_list, i, j + 1) == 1)
							return (1);
						printf("do the heredoc\n");
						j++;
						break ;
					}
					if (parse_list->tkns_array[i][1] == '>')
					{
						if (check_file_and_delim_name(parse_list, i, j + 1) == 1)
							return (1);
						printf("do the redir out\n");
						break ;
					}
					if (check_file_and_delim_name(parse_list, i, j) == 1)
						return (1);
					printf("do the redir in(parse_list->tkns_array[i+1][0])\n");
					//redir avec parse_list->tkns_array[i+1][0];
					//c'est le fichier à ouvrir
				}
				if (parse_list->tkns_array[i][0] == '>')
				{
					if (parse_list->tkns_array[i][1] == '>')
					{
						if (check_file_and_delim_name(parse_list, i , j + 1) == 1)
							return (1);
						printf("do_the_append_out\n");
						j++;
						break ;
					}
					if (parse_list->tkns_array[i][1] == '|' || parse_list->tkns_array[i][1] == '\0')
					{
						if (check_file_and_delim_name(parse_list, i, j + 1) == 1)
							return (1);
						printf("do the redir out\n");
						break ;
					}
				}
				if (parse_list->tkns_array[i][0] == '|')
				{
					if (check_pipe_name(parse_list, i, j) == 1)
						return (1);
					printf("do the pipe\n");
					break ;
				}
				if (parse_list->tkns_array[i][1] != '\0')
				{
					printf("Dundershell: syntax error near unexpected token `%c'\n", parse_list->tkns_array[i][1]);
					return (1);
				}
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

void	prep_next_node(t_parsing *parse_list, int ind_vector, int ind_array)
{
	parse_list->tkns_list->next = calloc(sizeof(t_tkns), 1);
	parse_list->tkns_list->next->prev = parse_list->tkns_list;
	parse_list->tkns_list->next->start = parse_list->tkns_list->start;
	parse_list->tkns_list->vector_cmd[ind_vector] = NULL;
	parse_list->tkns_list = parse_list->tkns_list->next;
	parse_list->tkns_list->vector_cmd = calloc(sizeof(char **),
			(count_cmd(parse_list->tkns_array, ind_array + 1) + 1));
	parse_list->tkns_list->argv_pos = parse_list->tkns_list->prev->argv_pos + 1;
	parse_list->tkns_list->vector_cmd[0]
		= calloc(ft_strlen(parse_list->tkns_array[++ind_array])
			+ 1, sizeof(char));
	parse_list->nb_of_pipes++;
	parse_list->i_vect = 0;
	parse_list->i_arr++;
	parse_list->i_str = 0;
}

void	alloc_vector(t_parsing *parse_list, int ind_vector,
	int ind_array, bool to_free)
{
	if (to_free == true)
		free(parse_list->tkns_list->vector_cmd[ind_vector]);
	parse_list->tkns_list->vector_cmd[ind_vector]
		= calloc(ft_strlen(parse_list->tkns_array[ind_array])
			+ 1, sizeof(char));
	parse_list->i_str = 0;
}

int	is_it_redir(t_parsing *parse_list)
{
	if (ft_strchr("<>", parse_list->tkns_array[parse_list->i_arr][parse_list->i_str]))
	{
		parse_list->i_arr += 2;
		if (parse_list->tkns_array[parse_list->i_arr - 1] == NULL
			|| parse_list->tkns_array[parse_list->i_arr] == NULL)
		{
			parse_list->tkns_list->vector_cmd[parse_list->i_vect] = NULL;
			return (1);
		}
		alloc_vector(parse_list, parse_list->i_vect, parse_list->i_arr, true);
		return (0);
	}
	return (2);
}

int	is_it_pipe(t_parsing *parse_list)
{
	if (ft_strchr("|", parse_list->tkns_array[parse_list->i_arr]
			[parse_list->i_str]))
	{
		if (parse_list->i_vect == 0
			&& parse_list->tkns_list->vector_cmd[parse_list->i_vect][0] == '\0')
		{
			parse_list->i_arr++;
			alloc_vector(parse_list, parse_list->i_vect,
				parse_list->i_arr, true);
			return (0);
		}
		prep_next_node(parse_list, parse_list->i_vect, parse_list->i_arr);
		return (0);
	}
	return (1);
}

// int	check_heredocs(t_parsing *parse_list)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (parse_list->tkns_array[i])
// 	{
// 		while (parse_list->tkns_array[i][j])
// 		{
// 			if (parse_list->tkns_array[i][j] == '<'
// 				&& parse_list->tkns_array[i][j + 1] == '<'
// 				&& j == 0)
// 			{
// 				if (check_file_and_delim_name(parse_list, i, j + 1) == 1)
// 					return (1);
// 				printf("do_heredoc(parse_list)\n");
// 				j++;
// 				break ;
// 			}
// 			j++;
// 		}
// 		j = 0;
// 		i++;
// 	}
// 	return (0);
// }
