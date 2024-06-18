#include "../include/minishell.h"


/*
	// DEBUG - HERE WE HAD A PROBLEM WHEN WE HAVE A LINE LIKE 
	< notes.txt > out where there is not parse_lit->tkns_array[parse_list->i_arr] (no command)
	I added some check in the while loop 
*/
t_parsing	*get_cmd(t_parsing *parse_list)
{
	parse_list->vector_cmd = ft_calloc(parse_list->cmd_count, sizeof(char **));
	
	printf("I am after calloc of vector\n");
	parse_list->start = parse_list->tkns_list;
	while (parse_list->tkns_list)
	{
		if (parse_list->tkns_list->tok_type == CMD)
		{
			//alloc_vector(parse_list, parse_list->i_vect, parse_list->i_arr, false);
			parse_list = do_copy_cmd(parse_list, parse_list->tkns_list->data);
			parse_list->i_vect++;
		}
		if (parse_list->tkns_list->next)
			parse_list->tkns_list = parse_list->tkns_list->next;
		else
			break ;
	}
	printf("I am after vectorisation\n");
	parse_list->tkns_list = parse_list->start;
	parse_list->tkns_list->vector_cmd = parse_list->vector_cmd;
	return (parse_list);
}


void	init_master_list(t_parsing *parse_list, int status)
{
//	parse_list->nb_of_pipes = 0;
//	parse_list->i_arr = 0;
//	parse_list->i_str = 0;
//	parse_list->i_vect = 0;
	parse_list->infile = 0;
	parse_list->outfile = 1;
//	parse_list->b_in = false;
//	parse_list->cmd = false;
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
	while (line[i] != '\0' && line[i] != parse_list->quote_type && i > 0)
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
	parse_list->tkns_list = init_list(line);
	parse_list = new_split(line, parse_list);		//is the parse list actually ok??
	printf("token is ==== %s\n", parse_list->tkns_list->data);
//	if (parse_list->tkns_list == NULL) // pk ça return NULL ça peux-tu me l'écrire dans la description de la fonction @JR ? ALEX note: null retourne seulement si la *line de depart est vide... idk si cest un check necessaire ou fait plus tot?
//		return (NULL);
	parse_list = check_metachar(parse_list); // pk ça return NULL ça peux-tu me l'écrire dans la description de la fonction @JR ?
//	printf("I am just before get cmd function 2 %s\n", parse_list->tkns_list->data);
	printf("I am before get_cmd\n");
	parse_list = get_cmd(parse_list);
	printf("I am after get_cmd\n");
	//parse_list->tkns_list = expend_var(); TODO : expend variabled
	//print_tkns_array_debug(*(parse_list));
//	printf("I am the vector before returning : %s\n", parse_list->tkns_list->vector_cmd[1]);
	return (parse_list);
}

bool	ft_isspace(char c)
{
	if (c == ' ' || c == '	')
		return (true);
	return (false);
}

char	**make_minitab(char *str)
{
	char **new_str;
	int tab;
	int i;
	int y;

	i = 0;
	tab = 0;
	new_str = malloc(sizeof(char **));
	while (str[i] != '\0')
	{
		while (ft_isspace(str[i]) == true && str[i])
			i++;
		new_str[tab] = malloc(sizeof(char *));
		y = 0;
		while (ft_isspace(str[i]) == false && str[i])
		{
			new_str[tab][y] = str[i];
			i++;
			y++;
		}
		new_str[tab][y] = '\0';
		printf("i am the tab function : %s\n", new_str[tab]);
		tab++;
	}
	return (new_str);
}

t_parsing	*do_copy_cmd(t_parsing *parse_list, char *str) //how is the vector_cmd used. this could be 1 and only 1 function to tranform from list to tab(vector)
{
	int i;
	int y;
	char **cmd_sep;
	int count;

	y = 0;
	count = 0;
	cmd_sep = make_minitab(str);
	while (cmd_sep[count])
		count++;
	while (y < count)
	{
		i = 0;
		parse_list->vector_cmd[parse_list->i_vect] = ft_calloc(ft_strlen(cmd_sep[y]), sizeof(char *));
		printf("I am after vector small alloc\n");
		while (parse_list && cmd_sep[y][i] != '\0' && cmd_sep[y] != NULL)
		{
			parse_list->vector_cmd[parse_list->i_vect][i]
				= cmd_sep[y][i];
			i++;
		}
		parse_list->vector_cmd[parse_list->i_vect][i] = '\0';
		printf("I am the vector: %s\n", parse_list->vector_cmd[parse_list->i_vect]);
		y++;
		if (y < count - 1)
			parse_list->i_vect++;
		else
			break ;
	}
	printf("I am after data is entered in vector\n");
	return (parse_list);
}