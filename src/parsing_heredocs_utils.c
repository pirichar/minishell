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
#include "arena.h"
#include <signal.h>

void	stop_heredoc(int signal)
{
	(void)signal;
	write(STDERR_FILENO, "\n", 1);
	exit(INTERRUPT_SIG);
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
		write(p_l->file, p_l->buf, ft_strlen(p_l->buf));
		free(tmp);
	}
	close(p_l->file);
	free(tmp);
	free_strrarr(g_ex.new_env);
	arena_free(&g_ex.arena);
	exit(0);
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
	p_l->file = open("./div/here_doc", O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (p_l->file == -1)
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
	p_l->infile = open("./div/here_doc", O_RDONLY);
	return (0);
}
