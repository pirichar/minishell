/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 12:47:29 by pirichar          #+#    #+#             */
/*   Updated: 2022/06/08 19:53:13 by pirichar         ###   ########.fr       */
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
# include "./Libft/libft/libft.h"
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

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

typedef struct s_cmds
{
	char			*cmd;
	int				flags;  // 0 = exe, 1 = redirection, 2 = flags, 3 = &&, 4 = pipe, 5 = $var, 6 = param
	bool			quotes;
	bool			close_quotes;
	struct s_cmds	*next;
	struct s_cmds	*prev;
	struct s_cmds	*start;

}			t_cmds;

typedef struct s_parsing
{
	int		nb_quote;
	bool	quotes;
	int		nb_dbquote;
	bool	dbquotes;
	int		nb_pipe;
	int		nb_cmd;
	int		sing_quotes;
	int		doub_quotes;
	int 	sml_then;
	int		gtr_then;
	int		dlr_sign;
	int 	and_sign;
	int 	*pids;//to be malloced with the right number of commands during the first phase of parsing
	char 	**cmds;// probably a linked list here ; for now ima malloc like 10 commands when init // FOR SURE NEED LIST WITH EACH COMMAND AND ARGUMENTS WITH THEIR POSITITION IN THE CHAIN
	int		nb_tokens;
	t_cmds	*commands;
	char	*user;
}				t_parsing;


//logo
void			print_logo(char **env);
//environement.c
bool			search_path(const char *p_arr, const char *cmd);
char			**var_to_strarr(char **env, char *var);
char 			**copy_strarr(char **env);
char			*var_to_str(char **env, char *var);
//pipex.c
int				calling_the_execs(int argc, char **argv,
					char **env, t_files *f);
void			execute_solo(const char *cmd, pid_t *p, char **env);
void			execute_out(const char *cmd, int fds[2], int *p, char **env);
int				execute(const char *cmd, int fd_in, int *p, char **env);
void			parse_and_exec_cmd(const char *cmd, char **env);
char			**split_cmd(const char *path, const char *cmd);
//builtin
void	look_for_builtins(char **s_line, char **new_env, bool *b_in);
//parsing
int				start_parse(char *line, char *env[]);
int				nb_tokens(t_parsing *parse_list, char *line);
void			init_parse(t_parsing *parse_list);
char			*tokenization(char *line, int i, t_parsing *parse_list);
int				cnt_tokens(char **cmds);
int				put_on_the_props(t_parsing *parse_list, char *env[]);
int				check_tokens(char *cmd, t_parsing *parse_list, char *env[]);
int				check_exe(char *cmd, char *env[]);
void			free_them(t_parsing *parse_list);
int				still_parsing(t_parsing *parse_list);

#endif