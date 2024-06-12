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
# include "./Libft/libft/libft.h"
# include <errno.h>
#include <signal.h>
#include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

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

typedef struct	s_exec
{
	char	*line;
	char	**s_line;
	char	**path;
	char	**new_env;
	char	*prompt;
	int		status;
	int		cmd_rtn;
	int 	foreground_job_active;  // 0 means no job is active, 1 means a job is active
	volatile sig_atomic_t interrupted;  // Flag to indicate interruption by SIGINT - VALIDER SI JE PREND ÇA OU UN INT 
	struct sigaction sa_int;
	struct sigaction sa_quit;
}				t_exec;

// ex est ma seul variable globale pour l'instant , je l'utilise avec les signaux et à travers l'exécution en général
// pour des raison de facilite d'acces j'ai choisi cette variable comme variable global
t_exec		*ex;

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
	char			**vector_cmd;
	int				argv_pos;
	int				tok_type;
	bool			sing_quotes;
	bool			dollar_sign;
	bool			b_in;
	char			*data;
	struct s_tkns	*next;
	struct s_tkns	*prev;
	struct s_tkns	*start;

}			t_tkns;

typedef struct s_parsing
{
	int 	*pids;//to be malloced with the right number of commands during the first phase of parsing
	t_tkns	*tkns_array;// probably a linked list here ; for now ima malloc like 10 commands when init // FOR SURE NEED LIST WITH EACH COMMAND AND ARGUMENTS WITH THEIR POSITITION IN THE CHAIN
	t_tkns	*tkns_list;
	char	*user;
	char	*line;
	char	**s_line;
	int		index;
	int		nb_of_pipes;
	int		i_arr;
	int		i_vect;
	int		i_str;
	int		infile;
	int		outfile;
	bool	b_in;
	bool	cmd;
	int		status;
	bool	with_nl;
	bool	check_nl;
	int		i;
	char 	*to_unset;
	t_exec 	*ex;
	int		file;
	char	*buf;
	int		quote_start;
	int		quote_end;
	char	quote_type;
	int		quote_count;
	bool	quotes;
	int		cmd_count;
	//pe ajouter un pointeur vers la struct t_exec ex pour avoir en tout temps accès 
}				t_parsing;


//main.c
void			print_logo(char **env);
void 			prompt_and_read_input();
//builtin
void			look_for_builtins(char ***s_line, char ***new_env, t_parsing *parse);
void			set_variable(char ***env, char *var, char *new_var);
//caling_the_exec_shell.c
void			calling_the_execs_shell(char **cmd, char ***new_env, t_parsing *parse);
void			parse_and_exec_cmd_shell(char **cmd, char **env);
//cd.c
void			go_to_home(char ***new_env);
void			mini_cd(char **s_line, char ***new_env,  t_parsing *parse);
//echo.c
void			mini_echo(char **s_line, t_parsing *parse);
bool			check_only_n(char *str);
void			parse_echo(char **s_line, bool *check_nl, bool *with_nl, int *i);
//env.c
void			mini_env(char **new_env,  t_parsing *parse);
int				ft_strcmp(const char *s1, const char *s2);
void			print_out_dir(char **to_print);
//environement.c
bool			search_path(const char *p_arr, const char *cmd);
char			**path_to_starrr(char **env, char *var);
char			*var_to_str(char **env, char *var);
bool			search_path_exec(const char *p_arr, const char *cmd);
//exit.c
void			exit_was_too_long(char **s_line);
void			mini_exit(char **s_line, t_parsing *parse);
//execute.c
int				execute(int fd_in, int *p, char **env, t_parsing *parse);
//execute_out.c
void			execute_out(char **cmd, int fds[2], char **env, t_parsing *parse);
//execute_solo.c
void			execute_solo(char **cmd, char ***env, t_parsing *parse);
//export.c
char			**bubble_sort_strarr(char **rtn);
char			**sort_strarr(char **to_sort);
void			print_export(char ***new_env);
void			actually_set_variables(char **s_line, char ***new_env);
void			mini_export(char **s_line, char ***new_env, t_parsing *parse);
//ft_strjoin_free.c
char	*ft_strjoin_free(char *s1, const char *s2);
//look_for.c
bool			look_for_exit(char **s_line);
bool			look_for_export(char **s_line);
bool			look_for_unset(char **s_line);
bool			look_for_cd(char **s_line);
bool			look_for_echo(char **s_line);
//pwd.c
void			mini_pwd(t_parsing *parse);
//signals
void handle_sigint(int sig);
void handle_sigquit(int sig);
void setup_signal_handlers();
void update_sigquit_handling();

//str_arr_fcn.c
void			free_strrarr(char **to_free);
int				strarr_len(char **str_arr);
char 			**copy_strarr(char **env);
void			set_3_variables(char ***env);
//unset.c
char*			return_variable(char **env, char *var);
void			mini_unset(char **s_line, char ***new_env,  t_parsing *parse);
//wait_for_pids.c
void	wait_for_pids(t_parsing *parse);

//prompt
char			*pwd_not_there(char *blue_user);
char			*pwd_prompt(char *new_env[], char *blue_user);
char			*set_prompt(char *new_env[]);
//parsing
t_parsing		*start_parse(char *line, int status);
int				init_first_token_nodes(t_parsing *parse_list);
char			**split(const char *s);
// int				check_file_and_delim_name(t_parsing *parse_list, int i, int j);
// int				check_pipe_name(t_parsing *parse_list, int i, int j);
int				count_cmd(t_tkns *tkns_list);
t_parsing	*get_cmd(t_parsing *parse_list);
void			print_tkns_array_debug(t_parsing parse_list);
int				check_metachar(t_parsing *parse_list);
void			prep_next_node(t_parsing *parse_list, int ind_vector, int ind_array);
void			alloc_vector(t_parsing *parse_list, int ind_vector, int ind_array, bool to_free);
int				is_it_redir(t_parsing *parse_list);
int				is_it_pipe(t_parsing *parse_list);
t_parsing	*do_copy_cmd(t_parsing *parse_list, char *tkns_list);

//new_parsing
t_parsing 		*new_split(char *s, t_parsing *parse_list);
int				check_file_and_delim_name(t_tkns *tkns_list);
int				check_pipe_name(t_tkns *tkns_array);

#endif