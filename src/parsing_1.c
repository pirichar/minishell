#include "../include/minishell.h"

int	get_cmd(t_parsing *parse_list)
{
	int	count;
	int	ind_array;
	int	ind_str;
	int	ind_vector;

	count = 0;
	ind_array = 0;
	ind_str = 0;
	ind_vector = 0;
	count = count_cmd(parse_list);
	printf("count %d\n", count);
	parse_list->tkns_list->vector_cmd = calloc(sizeof(char **), count + 1);
	while (parse_list->tkns_array[ind_array])
	{
		parse_list->tkns_list->vector_cmd[ind_vector] = calloc(ft_strlen(parse_list->tkns_array[ind_array]) + 1, sizeof(char));
		while (parse_list->tkns_array[ind_array][ind_str])
		{
			if (ft_strchr("<>", parse_list->tkns_array[ind_array][ind_str]))
			{
				ind_array += 2;
				if (parse_list->tkns_array[ind_array - 1] == NULL || parse_list->tkns_array[ind_array] == NULL)
				{
					parse_list->tkns_list->vector_cmd[ind_vector] = NULL;
					return (0);
				}
				free(parse_list->tkns_list->vector_cmd[ind_vector]);
				parse_list->tkns_list->vector_cmd[ind_vector] = calloc(ft_strlen(parse_list->tkns_array[ind_array]) + 1, sizeof(char));
				continue ;
			}
			if (ft_strchr("|", parse_list->tkns_array[ind_array][ind_str]))
			{
				parse_list->tkns_list->next = calloc(sizeof(t_tkns), 1);
				parse_list->tkns_list->next->prev = parse_list->tkns_list;
				parse_list->tkns_list->next->start = parse_list->tkns_list->start;
				parse_list->tkns_list->vector_cmd[ind_vector] = NULL;
				parse_list->tkns_list = parse_list->tkns_list->next;
				parse_list->tkns_list->vector_cmd = calloc(sizeof(char **), count + 1);
				ind_vector = 0;
				parse_list->tkns_list->argv_pos = parse_list->tkns_list->prev->argv_pos + 1;
				parse_list->tkns_list->vector_cmd[ind_vector] = calloc(ft_strlen(parse_list->tkns_array[ind_array]) + 1, sizeof(char));
				parse_list->nb_of_pipes++;
				ind_array++;
				ind_str = 0;
				continue ;
			}
			parse_list->tkns_list->vector_cmd[ind_vector][ind_str] = parse_list->tkns_array[ind_array][ind_str];
			ind_str++;
		}
		ind_str = 0;
		ind_array++;
		ind_vector++;
	}
	parse_list->tkns_list->vector_cmd[ind_vector] = NULL;
	return (0);
}

void	init_master_list(t_parsing *parse_list)
{
	parse_list->nb_of_pipes = 0;
}

t_parsing	*start_parse(char *line)
{
	t_parsing	*parse_list;

	parse_list = calloc(1, sizeof(t_parsing));
	init_master_list(parse_list);
	init_first_token_nodes(parse_list);
	parse_list->tkns_array = ft_split(line, ' ');
	if (parse_list->tkns_array == NULL)
		return (NULL);
	init_first_token_nodes(parse_list);
	if (check_heredocs(parse_list) != 0)
		return (NULL);
	if (check_redir_in(parse_list) != 0)
		return (NULL);
	if (check_redir_out(parse_list) != 0)
		return (NULL);
	// if (check_pipe(parse_list) != 0)
	// 	return (NULL);
	get_cmd(parse_list);
	print_tkns_array_debug(parse_list);
	return (parse_list);
}
