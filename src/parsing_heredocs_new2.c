#include "../include/minishell.h"
#include <signal.h>

void	stop_heredoc(int signal)
{
	(void)signal;
	write(STDERR_FILENO, "\n", 1);
	exit(INTERRUPT_SIG);
}

/**
 * @brief 
 * //TODO: should call the exit function here instead of returning 1
 * @param parse_list 
 * @return int 
 */
int	do_trunc(t_parsing *p_l)
{
	pid_t pid;
	int w_status;

	if (check_file_and_delim_name(p_l->tkns_list) == 1)
		return (1);
	p_l->file = open("./div/here_doc", O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (p_l->file == -1)
		return (1);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, &stop_heredoc);
		while (1)
		{
			p_l->buf = readline("heredoc> ");
			if (p_l->buf == NULL)
				break;
			if (!ft_strcmp(p_l->tkns_list->next->data, p_l->buf))
				break ;
			p_l->buf =  ft_strjoin(p_l->buf, "\n");
			write(p_l->file, p_l->buf, ft_strlen(p_l->buf));
			free (p_l->buf);
		}
		free (p_l->buf);
		close(p_l->file);
		p_l->infile = open("./div/here_doc", O_RDONLY);
		exit(0);
	}
	waitpid(pid, &w_status, 0);
	signal(SIGINT, &handle_sigint);
	if (WIFEXITED(w_status) && WEXITSTATUS(w_status) == INTERRUPT_SIG)
	{
		g_ex.fail_heredoc = true;
		return(1);
	}
	p_l->infile = open("./div/here_doc", O_RDONLY);
	return(0);
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
