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
	char			**vector_cmd;
	int				argv_pos;
	bool			sing_quotes;
	bool			dollar_sign;
	struct s_tkns	*next;
	struct s_tkns	*prev;
	struct s_tkns	*start;

}			t_tkns;

typedef struct s_parsing
{
	int 	*pids;//to be malloced with the right number of commands during the first phase of parsing
	char 	**tkns_array;// probably a linked list here ; for now ima malloc like 10 commands when init // FOR SURE NEED LIST WITH EACH COMMAND AND ARGUMENTS WITH THEIR POSITITION IN THE CHAIN
	t_tkns	*tkns_list;
	char	*user;
	int		index;
	int		nb_of_pipes;
	int		i_arr;
	int		i_vect;
	int		i_str;
}				t_parsing;


//logo
void			print_logo(char **env);
//environement.c
bool			search_path(const char *p_arr, const char *cmd);
char			**path_to_starrr(char **env, char *var);
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
void			look_for_builtins(char **line, char ***s_line, char ***new_env, bool *b_in);
void			set_variable(char ***env, char *var, char *new_var);

//exit.c
void			exit_was_too_long(char **s_line);
void			mini_exit(char *line, char **s_line, bool *b_in);
//export.c
char			**bubble_sort_strarr(char **rtn);
char			**sort_strarr(char **to_sort);
void			print_export(char ***new_env);
void			actually_set_variables(char **s_line, char ***new_env);
void			mini_export(char **s_line, char ***new_env, bool *b_in);
//env.c
void			mini_env(char **new_env, bool *b_in);
int				ft_strcmp(const char *s1, const char *s2);
void			print_out_dir(char **to_print);
//unset.c
char*			return_variable(char **env, char *var);
void			mini_unset(char **s_line, char ***new_env, bool *built_in);
//pwd.c
void			mini_pwd(bool *b_in);
//echo.c
void			mini_echo(char **s_line, bool *b_in);
bool			check_only_n(char *str);
void			parse_echo(char **s_line, bool *check_nl, bool *with_nl, int *i);
//tmp_star_function.c
int				get_nb_items_in_folder(void);
int				get_nb_items_chars_in_folder(void);
char			*mom_i_am_a_star(char *to_replace);
char			**mom_i_am_a_star_d(void);
void			mom_i_am_a_star_p(void);
//cd.c
void			go_to_home(char ***new_env);
void			mini_cd(char **s_line, char ***new_env, bool *b_in);
//str_arr_fcn.c
void			free_strrarr(char **to_free);
int				strarr_len(char **str_arr);
char 			**copy_strarr(char **env);
void			set_3_variables(char ***env);
//ft_strjoin_free.c
char	*ft_strjoin_free(char *s1, const char *s2);

//prompt
char			*pwd_not_there(char *blue_user);
char			*pwd_prompt(char *new_env[], char *blue_user);
char			*set_prompt(char *new_env[]);
//parsing
t_parsing		*start_parse(char *line);
int				init_first_token_nodes(t_parsing *parse_list);
char			**split(const char *s);
t_parsing		*start_parse(char *line);
int				check_file_and_delim_name(t_parsing *parse_list, int i, int j);
int				check_pipe_name(t_parsing *parse_list, int i, int j);
int				count_cmd(char **tkns_array, int ind_array);
int				get_cmd(t_parsing *parse_list);
void			print_tkns_array_debug(t_parsing *parse_list);
int				check_metachar(t_parsing *parse_list);
void			prep_next_node(t_parsing *parse_list, int ind_vector, int ind_array);
void			alloc_vector(t_parsing *parse_list, int ind_vector, int ind_array, bool to_free);
int				is_it_redir(t_parsing *parse_list);
int				is_it_pipe(t_parsing *parse_list);
void			do_copy_cmd(t_parsing *parse_list);

#endif