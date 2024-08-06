/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_heredocs_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandrinedube <alexandrinedube@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:35:55 by adube             #+#    #+#             */
/*   Updated: 2024/07/31 12:47:55 by alexandrine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	stop_heredoc(int signal)
{
	(void)signal;
	write(STDERR_FILENO, "\n", 1);
	close(g_ex.file);
	clean_and_exit(INTERRUPT_SIG);
}

void	trunc_child(t_parsing *p_l)
{
	char	*tmp;

	signal(SIGINT, &stop_heredoc);
	while (1)
	{
		tmp = readline("heredoc> ");
		if (tmp == NULL)
			break ;
		if (!ft_strcmp(p_l->tkns_list->next->data, tmp))
			break ;
		p_l->buf = ft_strjoin_arena(tmp, "\n");
		write(g_ex.file, p_l->buf, ft_strlen(p_l->buf));
		free(tmp);
	}
	close(g_ex.file);
	if (p_l->infile != 0)
		close(p_l->infile);
	free(tmp);
	clean_and_exit(0);
}

/**
 * @brief 
 * //TODO: should call the exit function here instead of returning 1
 * @param parse_list 
 * @return int 
 */
int	do_trunc(t_parsing *p_l)
{
	pid_t	pid;
	int		w_status;

	if (check_file_and_delim_name(p_l->tkns_list) == 1)
		return (1);
	g_ex.file = open("./div/here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (g_ex.file == -1)
		return (1);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		trunc_child(p_l);
	waitpid(pid, &w_status, 0);
	signal(SIGINT, &handle_sigint);
	if (WIFEXITED(w_status) && WEXITSTATUS(w_status) == INTERRUPT_SIG)
	{
		g_ex.fail_heredoc = true;
		return (1);
	}
	close(g_ex.file);
	if (p_l->infile != 0)
		close(p_l->infile);
	p_l->infile = open("./div/here_doc", O_RDONLY);
	return (0);
}
