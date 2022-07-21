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

typedef struct s_tkns
{
	char			*tkn;
	int				argv_pos;
	int				flags;  // 0 = exe, 1 = redirection, 2 = param, 3 = &&, 4 = ||, 5 = pipe, 6 = $var, 7 = infile for redirect, 8 = heredocs, 9 = delimiter for heredocs, 10 = redirect out, 11 = file for redirect out, 12 = redirect out and append, 69 = error
	bool			db_quotes;
	bool			sing_quotes;
	bool			dollar_sign;
	struct s_tkns	*next;
	struct s_tkns	*prev;
	struct s_tkns	*start;

}			t_tkns;

typedef struct s_parsing
{
	bool	db_quotes;
	bool	sing_quotes;
	int 	*pids;//to be malloced with the right number of commands during the first phase of parsing
	char 	**tkns_array;// probably a linked list here ; for now ima malloc like 10 commands when init // FOR SURE NEED LIST WITH EACH COMMAND AND ARGUMENTS WITH THEIR POSITITION IN THE CHAIN
	t_tkns	*tkns_list;
	char	*user;
	int		i_str_list;
	int		index_array;
	int		index_str_array;
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
void			look_for_builtins(char **s_line, char ***new_env, bool *b_in);
void			set_variable(char ***env, char *var, char *new_var);
//prompt
char			*pwd_not_there(char *blue_user);
char			*pwd_prompt(char *new_env[], char *blue_user);
char			*set_prompt(char *new_env[]);
//parsing
int				start_parse(char *line);
int				cnt_tokens(char **cmds);
int				init_first_token_nodes(t_parsing *parse_list);
int				init_all_token_nodes(t_parsing *parse_list);
int				argv0(t_parsing *parse_list);
int				check_tokens(t_parsing *parse_list);
int				put_redirect_props(t_parsing *parse_list);
int				put_ampers_props(t_parsing *parse_list);
int				put_pipe_props(t_parsing *parse_list);
char			**split(const char *s);
int				ft_strlen_delim(char *str);
void			delim_on_first_node(t_parsing *parse_list, int nb);
void			delim_on_other_node(t_parsing *parse_list, int nb);
void			still_no_0(t_parsing *parse_list, int nb);
void			split_by_delims(t_parsing *parse_list);
int				check_delims(t_parsing *parse_list);
void			put_arg_pos(t_parsing *parse_list);
int				var_len(t_parsing *parse_list);
void			init_circular_list(t_parsing *parse_list);
int				is_it_ampersand(t_parsing *parse_list);
int				is_it_pipes(t_parsing *parse_list);
int				is_it_heredoc_or_in_redirec(t_parsing *parse_list);
int				is_it_redirec_out_or_append(t_parsing *parse_list);

#endif