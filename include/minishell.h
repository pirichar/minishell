/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 12:47:29 by pirichar          #+#    #+#             */
/*   Updated: 2022/06/08 09:11:03 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <sys/wait.h>
#include <sys/types.h>
#include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include "colors.h"
# include <errno.h>

typedef struct s_files
{
	char	infile;
	char	outfile;
	int		*pids;
	int		process_count;
	int		status;
	int		here_doc;
}				t_files;

typedef struct s_ptrs
{
	char	**path;
	char	*cmd_with_slash;
	char	**final_cmd;
	char	**cmd_split;
}				t_exec_ptrs;

typedef struct s_parsing
{
	int	nb_quote;
	bool	quotes;
	int	nb_dbquote;
	bool	dbquotes;
	int	nb_pipe;
	int	nb_cmd;
	int sml_then;
	int	gtr_then;
	int	dlr_sign;
	int and_sign;
	int *pids;//to be malloced with the right number of commands during the first phase of parsing
	char **cmds;// probably a linked list here ; for now ima malloc like 10 commands when init // FOR SURE NEED LIST WITH EACH COMMAND AND ARGUMENTS WITH THEIR POSITITION IN THE CHAIN
}				t_parsing;

//environement.c
bool			search_path(const char *p_arr, const char *cmd);
char			**var_to_strarr(char **env, char *var);
//ft_split.c
char			**ft_split(const char *s, char c);
//str_functions.c
char			*ft_strjoin(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
unsigned int	ft_strlen(const char *str);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
//pipex.c
int				calling_the_execs(int argc, char **argv,
					char **env, t_files *f);
void			execute_solo(const char *cmd, int fds[2], int *p, char **env);
void			execute_out(const char *cmd, int fds[2], int *p, char **env);
int				execute(const char *cmd, int fd_in, int *p, char **env);
void			parse_and_exec_cmd(const char *cmd, char **env);
char			**split_cmd(const char *path, const char *cmd);


#endif