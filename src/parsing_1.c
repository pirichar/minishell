#include "../include/minishell.h"


/*
	// DEBUG - HERE WE HAD A PROBLEM WHEN WE HAVE A LINE LIKE 
	< notes.txt > out where there is not parse_lit->tkns_array[parse_list->i_arr] (no command)
	I added some check in the while loop 
*/
int	get_cmd(t_parsing *parse_list)
{
	parse_list->tkns_list->vector_cmd = calloc(sizeof(char **),
			count_cmd(parse_list->tkns_array, parse_list->i_arr) + 1);
	while (parse_list->tkns_array[parse_list->i_arr])
	{
		alloc_vector(parse_list, parse_list->i_vect, parse_list->i_arr, false);
		while (parse_list && parse_list->tkns_array &&
		 parse_list->tkns_array[parse_list->i_arr] &&
		 parse_list->tkns_array[parse_list->i_arr][parse_list->i_str])
		{
			if (is_it_redir(parse_list) == 1)
				return (0);
			else if (is_it_redir(parse_list) == 0)
				continue ;
			if (is_it_pipe(parse_list) == 0)
				continue ;
			else
				do_copy_cmd(parse_list);
		}
		parse_list->i_str = 0;
		parse_list->i_arr++;
		parse_list->i_vect++;
	}
	return (0);
}

void	init_master_list(t_parsing *parse_list, int status)
{
	parse_list->nb_of_pipes = 0;
	parse_list->i_arr = 0;
	parse_list->i_str = 0;
	parse_list->i_vect = 0;
	parse_list->infile = 0;
	parse_list->outfile = 1;
	parse_list->b_in = false;
	parse_list->cmd = false;
	parse_list->status = status;
	parse_list->pids = ft_calloc(parse_list->nb_of_pipes + 1, sizeof(int));
	parse_list->file = open("./div/here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	close(parse_list->file);

}

t_parsing	*start_parse(char *line, int status)
{
	t_parsing	*parse_list;

	parse_list = calloc(1, sizeof(t_parsing));

	init_master_list(parse_list, status);
	init_first_token_nodes(parse_list);
	//printf("line ==== %s\n", line);
	parse_list->tkns_array = split_set_quotes(line, "<>|");
	//printf("first %s\n", parse_list->tkns_array[0]);
	if (parse_list->tkns_array == NULL) // pk ça return NULL ça peux-tu me l'écrire dans la description de la fonction @JR ?
		return (NULL);
	if (check_metachar(parse_list) != 0) // pk ça return NULL ça peux-tu me l'écrire dans la description de la fonction @JR ?
		return (NULL);
	get_cmd(parse_list);
	//print_tkns_array_debug(*(parse_list));
	return (parse_list);
}

void	do_copy_cmd(t_parsing *parse_list)
{
	if (parse_list && parse_list->tkns_array && parse_list->tkns_array[parse_list->i_arr])
	{
		parse_list->tkns_list->vector_cmd[parse_list->i_vect][parse_list->i_str]
			= parse_list->tkns_array[parse_list->i_arr][parse_list->i_str];
		parse_list->i_str++;
	}
}