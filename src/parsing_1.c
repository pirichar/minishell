#include "../include/minishell.h"


/*
	// DEBUG - HERE WE HAD A PROBLEM WHEN WE HAVE A LINE LIKE 
	< notes.txt > out where there is not parse_lit->tkns_array[parse_list->i_arr] (no command)
	I added some check in the while loop 
*/
t_parsing	*get_cmd(t_parsing *parse_list)
{
	parse_list->tkns_list->vector_cmd = calloc(sizeof(char **), parse_list->cmd_count);
	printf("I am after calloc of vector\n");
	while (parse_list->tkns_list != NULL)
	{
		if (parse_list->tkns_list->tok_type != CMD)
			continue ;
		else
		{
			//alloc_vector(parse_list, parse_list->i_vect, parse_list->i_arr, false);
			parse_list = do_copy_cmd(parse_list, parse_list->tkns_list->data);
			parse_list->i_vect++;
		}
	parse_list->tkns_list = parse_list->tkns_list->next;
	}
	printf("I am after vectorisation\n");
	printf("I am the vector before going out of get_cmd : %s\n", parse_list->tkns_list->prev->vector_cmd[parse_list->i_vect - 1]);
	return (parse_list);
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
	parse_list->quote_count = 0;
	parse_list->quote_start = 0;
	parse_list->quote_end = 0;
	parse_list->quote_type = EMPTY;
	parse_list->cmd_count = 0;
	parse_list->pids = ft_calloc(parse_list->nb_of_pipes + 1, sizeof(int)); //nb pipe est 0, faire cette étape plus tard??
	parse_list->file = open("./div/here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	close(parse_list->file);

}

t_parsing	*quotes_line(char *line, t_parsing *parse_list)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != 34 && line[i] != 39)
		i++;
	if (line[i] == 34 || line[i] == 39)
	{
		parse_list->quote_start = i;
		parse_list->quote_type = line[i];
	}
	i = ft_strlen(line) - 1;
	while (line[i] != '\0' && line[i] != parse_list->quote_type)
		i--;
	if (parse_list->quote_start != i)
	{
		parse_list->quote_end = i;
		parse_list->quotes = true;
	}
	return (parse_list);
}

char *del_quotes(t_parsing *parse_list, char *line)
{
	int i;
	int y;

	char *newline;
	i = 0;
	y = 0;

	newline = calloc(ft_strlen(line), sizeof(char *));
	while (line[i] != '\0')
	{
		if (line[i] != parse_list->quote_type)
		{
			newline[y] = line[i];
			y++;
		}
		else
			parse_list->quote_count++;
		i++;
	}
	parse_list->quote_end = parse_list->quote_end - parse_list->quote_count;
	newline[y] = '\0';
	return (newline);
}

t_parsing	*start_parse(char *line, int status)
{
	t_parsing	*parse_list;

	parse_list = calloc(1, sizeof(t_parsing));

	init_master_list(parse_list, status);
//	init_first_token_nodes(parse_list);
	printf("line ==== %s\n", line);
	parse_list = quotes_line(line, parse_list);    //new step, take care of quotes first
	if (parse_list->quotes == true)
		line = del_quotes(*&parse_list, line);
	printf("line after del_quotes ==== %s\n", line);
	parse_list = new_split(line, parse_list);		//is the parse list actually ok??
//	printf("token is ==== %s\n", parse_list->tkns_list->data);
//	if (parse_list->tkns_list == NULL) // pk ça return NULL ça peux-tu me l'écrire dans la description de la fonction @JR ? ALEX note: null retourne seulement si la *line de depart est vide... idk si cest un check necessaire ou fait plus tot?
//		return (NULL);
//	if (check_metachar(parse_list) != 0) // pk ça return NULL ça peux-tu me l'écrire dans la description de la fonction @JR ?
//		return (NULL);
//	printf("I am just before get cmd function 2 %s\n", parse_list->tkns_list->data);
	printf("I am before get_cmd\n");
	parse_list = get_cmd(parse_list);
	printf("I am after get_cmd\n");
	//parse_list->tkns_list = expend_var();
	//print_tkns_array_debug(*(parse_list));
//	printf("I am the vector before returning : %s\n", parse_list->tkns_list->vector_cmd[1]);
	return (parse_list);
}

t_parsing	*do_copy_cmd(t_parsing *parse_list, char *tkns_list) //how is the vector_cmd used. this could be 1 and only 1 function to tranform from list to tab(vector)
{
	int i;
	i = 0;
	parse_list->tkns_list->vector_cmd[parse_list->i_vect] = ft_calloc(sizeof(char *), ft_strlen(tkns_list));
	printf("I am after vector small alloc\n");
	while (parse_list && tkns_list[i] != '\0' && tkns_list != NULL)
	{
		parse_list->tkns_list->vector_cmd[parse_list->i_vect][i]
			= tkns_list[i];
		i++;
	}
	parse_list->tkns_list->vector_cmd[parse_list->i_vect][i] = '\0';
	printf("I am after data is entered in vector\n");
	printf("I am the vector: %s\n", parse_list->tkns_list->vector_cmd[parse_list->i_vect]);
	return (parse_list);
}