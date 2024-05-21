#include "../include/minishell.h"


/*
	// DEBUG - HERE WE HAD A PROBLEM WHEN WE HAVE A LINE LIKE 
	< notes.txt > out where there is not parse_lit->tkns_array[parse_list->i_arr] (no command)
	I added some check in the while loop 
*/
int	get_cmd(t_parsing *parse_list)
{
	int i;
	i = 0;
	parse_list->tkns_list->vector_cmd = calloc(sizeof(char **),
			count_cmd(parse_list->tkns_array, parse_list->i_arr) + 1);
	while (parse_list->tkns_list != NULL)
	{
		alloc_vector(parse_list, parse_list->i_vect, parse_list->i_arr, false);
		if (parse_list->tkns_list->tok_type != CMD)
			continue ;
		else
			do_copy_cmd(parse_list);
	parse_list->tkns_list = parse_list->tkns_list->next;
	}
	return (0);
}


void	init_master_list(t_parsing *parse_list, int status)
{
	parse_list->nb_of_pipes = 0;
	// parse_list->i_arr = 0;
	// parse_list->i_str = 0;
	// parse_list->i_vect = 0;
	parse_list->infile = 0;
	parse_list->outfile = 1;
	parse_list->b_in = false;
	parse_list->cmd = false;
	parse_list->status = status;
	parse_list->pids = ft_calloc(parse_list->nb_of_pipes + 1, sizeof(int)); //nb pipe est 0, faire cette étape plus tard??
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
	parse_list->tkns_list = new_split(line, "<>|");
	//printf("first %s\n", parse_list->tkns_array[0]);
	// if (parse_list->tkns_list == NULL) // pk ça return NULL ça peux-tu me l'écrire dans la description de la fonction @JR ? ALEX note: null retourne seulement si la *line de depart est vide... idk si cest un check necessaire ou fait plus tot?
	// 	return (NULL);
	if (check_metachar(parse_list) != 0) // pk ça return NULL ça peux-tu me l'écrire dans la description de la fonction @JR ?
		return (NULL);
	get_cmd(parse_list);
	//parse_list->tkns_list = del_quotes();
	//parse_list->tkns_list = expend_var();
	//print_tkns_array_debug(*(parse_list));
	return (parse_list);
}

void	do_copy_cmd(t_parsing *parse_list) //how is the vector_cmd used. this could be 1 and only 1 function to tranform ffrom list to tab(vector)
{
	if (parse_list && parse_list->tkns_list != NULL)
	{
		parse_list->tkns_list->vector_cmd[parse_list->i_vect][parse_list->i_str]
			= parse_list->tkns_array[parse_list->i_arr][parse_list->i_str];
		parse_list->i_str++;
	}
}