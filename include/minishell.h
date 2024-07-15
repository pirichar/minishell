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
# include "./colors.h"
# include "./libft/libft.h"
# include <errno.h>
#include <signal.h>
#include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../src/arena.h"

# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define OUTPUT 6
# define PIPE 7
# define IN_OUT 8
# define SPECIAL_PIPE 9
# define TRUNC_ARG 10
# define INTERRUPT_SIG 130

typedef struct	s_exec
{
	char	*line;
	char	**s_line;
	char	**new_env;
	char	*prompt;
	int		child_rtn;
	int		status;
	int		cmd_rtn;
	bool	fail_heredoc;
	bool	only_delim;
	t_arena arena;
}				t_exec;

// ex est ma seul variable globale pour l'instant , je l'utilise avec les signaux et à travers l'exécution en général
// pour des raison de facilite d'acces j'ai choisi cette variable comme variable global
extern t_exec		g_ex;

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

//token list
//si ya pas de pipe ya juste une token avec un vecteur de commande
//le vecteur de commande c'est ce qui est feed a execve
//arggv pos = 0 premiere exectute; 1= après un pipe etc.
//il va falloir rajouter des bool redir in; redir out; heredoc
typedef struct s_tkns
{
	int				tok_type;
	char			**vector_cmd;
	bool			dollar_sign;
	char			*data;
	struct s_tkns	*next;
	struct s_tkns	*prev;

}			t_tkns;

typedef struct s_parsing
{
	int 	*pids;
	t_tkns	*tkns_list;
	t_tkns	*start;
	t_tkns	*old;
	char	**vector_cmd;
	char	*line;
	int		nb_of_pipes;
	int		i_vect;
	int		infile;
	int		outfile;
	bool	b_in;
	bool	f_command;
	int		status;
	bool	with_nl;
	bool	check_nl;
	int		i;
	char 	*to_unset;
	int		file;
	char	*buf;
	int		quote_start;
	int		quote_end;
	char	quote_type;
	int		quote_count;
	bool	quotes;
	int		cmd_count;
	char	***pipes_args;
	int		index;
	int		new_i;
	int		to_skip;
	int		p_x;
	int		p_y;
	int		p_start;
	char	*p_new;
	char	**trunc_args;
}				t_parsing;


//main.c
void	prompt_and_read_input(void);

//builtin
void			look_for_builtins(char ***s_line, char ***new_env, t_parsing *parse);
void			set_variable(char ***env, char *var, char *new_var);

//caling_the_exec_shell.c
void			calling_the_execs_shell(char **cmd, char ***new_env, t_parsing *parse);
void			parse_and_exec_cmd_shell(char **cmd, char **env);

//cd.c
void			mini_cd(char **s_line, char ***new_env,  t_parsing *parse);

//echo.c
void			mini_echo(char **s_line, t_parsing *parse);

//env.c
void			mini_env(char **new_env,  t_parsing *parse);
int				ft_strcmp(const char *s1, const char *s2);

void			print_out_dir(char **to_print);
//environement.c
char			**path_to_starrr(char **env, char *var);
char			*var_to_str(char **env, char *var);
bool			search_path_exec(const char *p_arr, const char *cmd);

//exit.c
void			mini_exit(char **s_line, t_parsing *parse);
void			ft_clean(t_parsing	**parse);
void			ft_exit(t_parsing* parse);

//execute.c
int				execute(int fd_in, int *p, char **env, t_parsing *parse);

//execute_out.c
void			execute_out(char **cmd, int fds[2], char **env, t_parsing *parse);

//execute_solo.c
void			execute_solo(char **cmd, char ***env, t_parsing *parse);

//export.c
char			**bubble_sort_strarr(char **rtn);
void			mini_export(char **s_line, char ***new_env, t_parsing *parse);

//ft_strjoin_free.c
char	*ft_strjoin_free(char *s1, const char *s2);

//logo_n_setup
void			print_logo(char **env);
void			configure_terminal(void);
int				setup_minishell(int argc, char **env);

//look_for.c
bool			look_for_exit(char **s_line);
bool			look_for_export(char **s_line);
bool			look_for_unset(char **s_line);
bool			look_for_cd(char **s_line);
bool			look_for_echo(char **s_line);

//pwd.c
void			mini_pwd(t_parsing *parse);

//signals
void setup_signal_handlers();

//str_arr_fcn.c
void			free_strrarr(char **to_free);
int				strarr_len(char **str_arr);
char 			**copy_env(char **env);

//unset.c
char*			return_variable(char **env, char *var);
void			mini_unset(char **s_line, char ***new_env,  t_parsing *parse);

//wait_for_pids.c
void	wait_for_pids(t_parsing *parse);

//prompt
char			*set_prompt(char *new_env[]);

//parsing_1.c
t_parsing		*start_parse(char *line, int status);
bool			ft_isspace(char c);
t_parsing	*do_copy_cmd(t_parsing *parse_list, char *str);
t_parsing	*do_copy_trunc_arg(t_parsing *parse_list);

//pasring_2.c
t_parsing	*get_cmd(t_parsing *parse_list);
void	init_master_list(t_parsing *parse_list, int status);
t_parsing	*quotes_line(char *line, t_parsing *parse_list);
char	*del_quotes(t_parsing *parse_list, char *line);
char	**prep_tab(t_tkns *tkns_list);

//parsing_3.c
void	helper_get_arg(t_parsing	*parse_list, int y, char ***tab_tab);
char	***get_argarray(t_parsing *parse_list);
char	*search_env(char *s, int search, t_parsing *p_list);
char	*joining(char *s1, char *s2, t_parsing *parse_list);
char	*expand_var(char *line, t_parsing *p_l);

//parsing_split.c
t_tkns	*set_toktype(t_tkns *matrix);
t_parsing	*new_split(char *s, t_parsing *parse_list);

//parsing_split2.c
t_tkns	*my_lstlast(t_tkns *lst);
void	nodeaddback(t_tkns **lst, t_tkns *new);
t_tkns	*make_node(t_tkns *matrix, char *s);
t_tkns	*node_redir(t_tkns *matrix, char *s, int size);
t_tkns	*init_list(char *s);

//parking_split_helper.c
bool	check_double_redir(char *s, t_parsing *parse_list);
bool	check_in_out_file(char *s, t_parsing *parse_list);
void	init_redir_node_two_char(char *s, t_parsing *parse_list);
void	init_redir_node_one_char(char *s, t_parsing *parse_list);
void	init_command_node(char *s, t_parsing *parse_list);

//parsing_here_doc_new.c
t_parsing		*check_metachar(t_parsing *parse_list);

//parsing_here_doc_new2.c
int	do_trunc(t_parsing *p_l);
int	do_in_out(t_parsing *parse_list);
int	do_input(t_parsing *parse_list);
int	do_append(t_parsing *parse_list);
int	do_output(t_parsing *parse_list);

// TODO je crois que rien n'est utilise dans ces fonctions a valider
//parsing_utils.c
int				check_file_and_delim_name(t_tkns *tkns_list);
void			print_tkns_array_debug(t_parsing parse_list);
int				count_cmd(t_tkns *tkns_list);
int				init_first_token_nodes(t_parsing *parse_list);
int				check_pipe_name(t_tkns *tkns_array);


// ft_signals
void	handle_sigint(int sig);


//arena_str
char	**ft_split_arena(const char *s, char c);
char	*ft_strjoin_arena(const char *s1, const char *s2);

#endif