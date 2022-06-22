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
	int				flags;  // 0 = exe, 1 = redirection, 2 = flags, 3 = &&, 4 = pipe, 5 = $var, 6 = param, 7 = infile for redirect 69 = error
	bool			db_quotes;
	bool			sing_quotes;
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
int				start_parse(char *line);
int				cnt_tokens(char **cmds);
int				put_on_the_props(t_parsing *parse_list);
int				assign_the_list(t_parsing *parse_list);
int				argv0(t_parsing *parse_list);
int				check_tokens(t_parsing *parse_list);
int				put_redirect_props(t_parsing *parse_list);
int				put_ampers_props(t_parsing *parse_list);
int				good_riddance_quotes(t_parsing *parse_list, int i);
char			**split(const char *s);

#endif