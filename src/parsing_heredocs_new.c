#include "../include/minishell.h"
#include <stdio.h>



if (parse_list->tkns_list->tok_type == TRUNC)
{
	if (check_file_and_delim_name(parse_list->tkns_list, j + 1) == 1)
		return (1);
	printf("do the heredoc\n");
	parse_list->file = open("./div/here_doc", O_CREAT | O_WRONLY | O_APPEND, 0777);	
	if (parse_list->file == -1)
		return (1);//should call the exit function here
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
	j++;
	break ;
}

if (parse_list->tkns_list->tok_type == OUT_IN)
{
	if (check_file_and_delim_name(parse_list->tkns_list, j + 1) == 1)
		return (1);
	printf("do the redir out\n");
	break ;
}

if (parse_list->tkns_list->tok_type == INPUT)
{
	if (check_file_and_delim_name(parse_list->tkns_list, j) == 1)
		return (1);
	parse_list->infile = open(parse_list->tkns_list->next->data, O_RDONLY);
	if (parse_list->infile == -1)
		fprintf(stderr, "Could not open input file\n");
	else
		fprintf("did the redir in this is parse_list->infile %d\n", parse_list->infile);
}