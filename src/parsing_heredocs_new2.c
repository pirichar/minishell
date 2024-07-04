#include "../include/minishell.h"

/**
 * @brief 
 * //TODO: should call the exit function here instead of returning 1
 * @param parse_list 
 * @return int 
 */
int	do_trunc(t_parsing *p_l)
{
	if (check_file_and_delim_name(p_l->tkns_list) == 1)
		return (1);
	p_l->file = open("./div/here_doc", O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (p_l->file == -1)
		return (1);
	while (1)
	{
		write(1, "heredoc>", 9);
		p_l->buf = get_next_line(0);
		if (!ft_strncmp(p_l->tkns_list->next->data,
				p_l->buf, ft_strlen(p_l->tkns_list->next->data)))
			break ;
		write(p_l->file, p_l->buf, ft_strlen(p_l->buf));
		free (p_l->buf);
	}
	free (p_l->buf);
	close(p_l->file);
	p_l->infile = open("./div/here_doc", O_RDONLY);
	return (0);
}

int	do_in_out(t_parsing *parse_list)
{
	if (check_file_and_delim_name(parse_list->tkns_list) == 1)
		return (1);
	return (0);
}

/**
 * @brief 

 * @param parse_list 
 * @return int 
 */
int	do_input(t_parsing *parse_list)
{
	if (check_file_and_delim_name(parse_list->tkns_list) == 1)
		return (1);
	parse_list->infile = open(parse_list->tkns_list->next->data, O_RDONLY);
	if (parse_list->infile == -1)
		fprintf(stderr, "Could not open input file\n");
	return (0);
}

int	do_append(t_parsing *parse_list)
{
	if (check_file_and_delim_name(parse_list->tkns_list) == 1)
		return (1);
	parse_list->outfile = open(parse_list->tkns_list->next->data,
			O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (parse_list->outfile == -1)
	{
		fprintf(stderr, "MINISHELL: Could not open output file\n");
		return (1);
	}
	return (0);
}

int	do_output(t_parsing *parse_list)
{
	if (check_file_and_delim_name(parse_list->tkns_list) == 1)
		return (1);
	parse_list->outfile = open(parse_list->tkns_list->next->data,
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (parse_list->outfile == -1)
	{
		fprintf(stderr, "MINISHELL: Could not open output file\n");
		return (1);
	}
	return (0);
}
