#include "../include/minishell.h"
#include <stdio.h>


int	do_trunc(t_parsing *parse_list)
{
	if (check_file_and_delim_name(parse_list->tkns_list) == 1)
		return (1);
	printf("do the heredoc\n");
	parse_list->file = open("./div/here_doc", O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (parse_list->file == -1)
		return (1);//TODO: should call the exit function here
	while (1)
	{
		write(1, "heredoc>", 9);
		parse_list->buf = get_next_line(0);
		if (!ft_strncmp(parse_list->tkns_list->next->data, parse_list->buf, ft_strlen(parse_list->tkns_list->next->data)))
			break ;
		write(parse_list->file, parse_list->buf, ft_strlen(parse_list->buf));
		free (parse_list->buf);
	}
	free (parse_list->buf);
	close(parse_list->file);
	parse_list->infile = open("./div/here_doc", O_RDONLY);
	return (0) ;
}

int	do_in_out(t_parsing *parse_list)
{
	if (check_file_and_delim_name(parse_list->tkns_list) == 1)
		return (1);
		printf("do the redir out\n");
	return (0) ;
}

int	do_input(t_parsing *parse_list)
{
	if (check_file_and_delim_name(parse_list->tkns_list) == 1)
		return (1);
	parse_list->infile = open(parse_list->tkns_list->next->data, O_RDONLY);
	if (parse_list->infile == -1)
		fprintf(stderr, "Could not open input file\n");
	else
		printf("did the redir in this is parse_list->infile %d\n", parse_list->infile);
	return (0);
}

int	do_append(t_parsing *parse_list)
{
	if (check_file_and_delim_name(parse_list->tkns_list) == 1)
		return (1);
	parse_list->outfile = open(parse_list->tkns_list->next->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (parse_list->outfile == -1)
	{
		fprintf(stderr, "MINISHELL: Could not open output file\n");
		return (1);
	}
	printf("did_the_append_out\n");
	return (0);
}

int	do_output(t_parsing *parse_list)
{
	if (check_file_and_delim_name(parse_list->tkns_list) == 1)
		return (1);
	parse_list->outfile = open(parse_list->tkns_list->next->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (parse_list->outfile == -1)
	{
		fprintf(stderr, "MINISHELL: Could not open output file\n");
		return (1);
	}
	printf("did the redir out\n");
	return (0);
}

int	do_pipe(t_parsing *parse_list)
{
	if (check_pipe_name(parse_list->tkns_list) == 1)
		return (1);
	printf("do the pipe\n");
	return (0);
}

t_parsing	*check_metachar(t_parsing *parse_list)
{
//	parse_list->tkns_list = parse_list->tkns_list->next;
	parse_list->start = parse_list->tkns_list;
	while (parse_list->tkns_list)
	{
		if (parse_list->tkns_list->tok_type == TRUNC)
			if (do_trunc(parse_list) == 1)
				return parse_list;//TODO exit command instead
		if (parse_list->tkns_list->tok_type == IN_OUT)
			if (do_in_out(parse_list) == 1)
				return parse_list;//TODO exit command instead				return (1);//TODO exit command
		if (parse_list->tkns_list->tok_type == INPUT)
			if (do_input(parse_list) == 1)
				return parse_list;//TODO exit command instead				return (1);//TODO exit command
		if (parse_list->tkns_list->tok_type == APPEND)
			if (do_append(parse_list) == 1)
				return parse_list;//TODO exit command instead				return (1);//TODO exit command
		if (parse_list->tkns_list->tok_type == PIPE)
			if (do_pipe(parse_list) == 1)
				return parse_list;//TODO exit command instead				return (1);//TODO exit command
		if (parse_list->tkns_list->tok_type == SPECIAL_PIPE || parse_list->tkns_list->tok_type == OUTPUT)
			if (do_output(parse_list) == 1)
				return parse_list;//TODO exit command instead				return (1); //TODO exit command
		if (parse_list->tkns_list->tok_type != CMD && parse_list->tkns_list->next)
			parse_list->tkns_list->next->tok_type = ARG;
		if (parse_list->tkns_list->next)
			parse_list->tkns_list = parse_list->tkns_list->next;
		else
			break ;
	}
	parse_list->tkns_list = parse_list->start;
	return (parse_list);
}
