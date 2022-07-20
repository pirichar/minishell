#include "../include/minishell.h"


int	strarr_len(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr[i])
		i++;
	return (i);
}

void	free_strrarr(char **to_free)
{
	int	i;

	i = 0;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
}

void	add_new_variable(char ***env, char *var, char *variable)
{
	int		i;
	char	**tmp;

	tmp = *env;
	i = strarr_len(*env);
	(*env) = ft_calloc(i + 2, sizeof(char *));
	i = 0;
	while (tmp[i])
	{
		(*env)[i] = ft_strdup(tmp[i]);
		i++;
	}
	(*env)[i] = ft_strjoin(var, variable);
	free_strrarr(tmp);
}

void	set_variable(char ***env, char *var, char *new_var)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], var, ft_strlen(var)) == 0)
		{
			tmp = (*env)[i];
			(*env)[i] = ft_strjoin(var, new_var);
			free(tmp);
			break ;
		}
		i++;
	}
	if ((*env)[i] == NULL)
		add_new_variable(env, var, new_var);
}

/*returns a copy of a variable or null if not found*/

char*	return_variable(char **env, char *var)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
		{
			return (env[i]);
		}
		i++;
	}
	return (NULL);
}

void	go_to_home(char ***new_env)
{
	char	**home;
	char	*actual_pwd;
	char	*buff;

	home = ft_split(return_variable(*new_env, "HOME"), '=');
	if (home == NULL)
		printf("minishell: cd: HOME not set\n");
	else
		chdir(home[1]);
	free_strrarr(home);
	buff = NULL;
	actual_pwd = getcwd(buff, 1024);
	set_variable(new_env, "PWD=", actual_pwd);
	free(actual_pwd);
	free(buff);
}

/*
	our version of CD;
	It used to change directory with every argument 
	like cd .. folder .. folder would get you back to folder
	But now its only one argument or getting you back to home
*/
void	mini_cd(char **s_line, char ***new_env, bool *b_in)
{
	char	*actual_pwd;
	char	*buff;

	*b_in = true;
	buff = NULL;
	actual_pwd = getcwd(buff, 1024);
	set_variable(new_env, "OLDPWD=", actual_pwd);
	free(actual_pwd);
	free(buff);
	if (s_line[1] == NULL)
	{
		go_to_home(new_env);
		return ;
	}
	if (s_line[1])
		chdir(s_line[1]);
	buff = NULL;
	actual_pwd = getcwd(buff, 1024);
	set_variable(new_env, "PWD=", actual_pwd);
	free(actual_pwd);
	free(buff);
}
//s'assurer que dans la version officielle echo "-n" 
// fonctionne aussi mais pas echo " -n"

bool	check_only_n(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

void	parse_echo(char **s_line, bool *check_nl, bool *with_nl, int *i)
{
	while (s_line[*(i)] && ft_strncmp(s_line[*(i)], "-n", 2) == 0
		&& (*check_nl))
	{
		if (check_only_n(s_line[*(i)]))
			(*with_nl) = false;
		else
			break ;
		(*i)++;
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	**bubble_sort_strarr(char **rtn)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (rtn[i + 1])
	{
		if (ft_strcmp(rtn[i], rtn[i + 1]) > 0)
		{
			tmp = rtn[i];
			rtn[i] = rtn[i + 1];
			rtn[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
	return (rtn);
}

int	get_nb_items_in_folder(void)
{
	DIR				*dir;
	struct dirent	*sd;
	int				i;

	i = 0;
	dir = opendir(".");
	if (dir == NULL)
	{
		printf("error ! Unable to open directory\n");
		return (-1);
	}
	while ((sd = readdir(dir)) != NULL)
	{
		if (*sd->d_name
			&& (ft_strncmp(sd->d_name, ".", ft_strlen(sd->d_name)) != 0)
			&& (ft_strncmp(sd->d_name, "..", ft_strlen(sd->d_name)) != 0))
			i++;
	}
	closedir(dir);
	return (i);
}

int	get_nb_items_chars_in_folder(void)
{
	DIR				*dir;
	struct dirent	*sd;
	int				i;
	int				j;

	i = 0;
	j = 0;
	dir = opendir(".");
	if (dir == NULL)
	{
		printf("error ! Unable to open directory\n");
		return (-1);
	}
	while ((sd = readdir(dir)) != NULL)
	{
		j = 0;
		if (*sd->d_name
			&& (ft_strncmp(sd->d_name, ".", ft_strlen(sd->d_name)) != 0)
			&& (ft_strncmp(sd->d_name, "..", ft_strlen(sd->d_name)) != 0))
		{
			while(sd->d_name[j++])
				i++;
			i++;
		}
	}
	closedir(dir);
	return (i);
}

void	print_out_dir(char **to_print)
{
	int	i;

	i = 0;
	to_print = bubble_sort_strarr(to_print);
	while (to_print[i])
		printf("%s ", to_print[i++]);
}

/*
	function that takes everything in the actual folder and returns it at a char*
	its not in order yet tho
*/
char	*mom_i_am_a_star(char *to_replace)
{
	DIR				*dir;
	struct dirent	*sd;
	int				i;
	char			*rtn;

	i = get_nb_items_chars_in_folder();
	if (i == -1)
		return (NULL);
	rtn = ft_calloc(i + 1, sizeof(char));
	i = 0;
	dir = opendir(".");
	while ((sd = readdir(dir)) != NULL)
	{
		if (*sd->d_name && sd->d_name[0] != '.'
			&& (ft_strncmp(sd->d_name, ".", ft_strlen(sd->d_name)) != 0)
			&& (ft_strncmp(sd->d_name, "..", ft_strlen(sd->d_name)) != 0))
		{
			rtn = ft_strjoin(rtn, " ");
			rtn = ft_strjoin(rtn, sd->d_name);
			i++;
		}
	}
	closedir (dir);
	free (to_replace);
	return (rtn);
}

/*
	function that takes everything in the actual folder and returns it at a char**
*/
char	**mom_i_am_a_star_d(void)
{
	DIR				*dir;
	struct dirent	*sd;
	int				i;
	char			**into_dir;

	i = get_nb_items_in_folder();
	if (i == -1)
		return NULL;
	into_dir = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	dir = opendir(".");
	while ((sd = readdir(dir)) != NULL)
	{
		if (*sd->d_name && sd->d_name[0] != '.'
			&& (ft_strncmp(sd->d_name, ".", ft_strlen(sd->d_name)) != 0)
			&& (ft_strncmp(sd->d_name, "..", ft_strlen(sd->d_name)) != 0))
		{
			into_dir[i] = ft_strdup(sd->d_name);
			i++;
		}
	}
	closedir(dir);
	into_dir = bubble_sort_strarr(into_dir);
	return (into_dir);
}
/*
	function that takes everything in the actual folder and print it out
*/
void	mom_i_am_a_star_p(void)
{
	DIR				*dir;
	struct dirent	*sd;
	int				i;
	char			**into_dir;

	i = get_nb_items_in_folder();
	if (i == -1)
		return ;
	into_dir = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	dir = opendir(".");
	while ((sd = readdir(dir)) != NULL)
	{
		if (*sd->d_name && sd->d_name[0] != '.'
			&& (ft_strncmp(sd->d_name, ".", ft_strlen(sd->d_name)) != 0)
			&& (ft_strncmp(sd->d_name, "..", ft_strlen(sd->d_name)) != 0))
		{
			into_dir[i] = ft_strdup(sd->d_name);
			i++;
		}
	}
	closedir(dir);
	print_out_dir(into_dir);
	free_strrarr(into_dir);
}

/*
	This function basically printf stuff
	It first look for -n -nnn and multiples -n
	Then once it filtered all the -n
	After that it set check_nl to false
	this way it does not look for flags
	to parse but print them out instead
*/
void	mini_echo(char **s_line, bool *b_in)
{
	int		i;
	int		j;
	bool	with_nl;
	bool	check_nl;

	i = 1;
	j = 1;
	with_nl = true;
	check_nl = true;
	*b_in = true;
	while (s_line[i])
	{
		parse_echo(s_line, &check_nl, &with_nl, &i);
		if (s_line[i] == NULL)
			return ;
		check_nl = false;
		if (s_line[i][0] == '*' && s_line[i][1] == 0)
		{
			mom_i_am_a_star_p();
			i++;
			continue;
		}
		if (s_line[i + 1])
			printf("%s ", s_line[i]);
		else
			printf("%s", s_line[i]);
		i++;
	}
	if (with_nl)
		printf("\n");
}

void	mini_pwd(bool *b_in)
{
	char	*to_print;
	char	*buff;

	*b_in = true;
	buff = NULL;
	to_print = getcwd(buff, 1024);
	printf("%s\n", to_print);
	free(to_print);
	free(buff);
}


void	mini_env(char **new_env, bool *b_in)
{
	int		i;
	char	**tmp;

	*b_in = true;
	i = 0;
	while (new_env[i])
	{
		tmp = ft_split(new_env[i], '=');
		if (tmp[1] != NULL)
			printf("%s\n", new_env[i]);
		free_strrarr(tmp);
		i++;
	}
}



char	**sort_strarr(char **to_sort)
{
	int		i;
	char	**rtn;

	i = 0;
	while (to_sort && to_sort[i])
		i++;
	rtn = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (to_sort[i])
	{
		rtn[i] = ft_strdup(to_sort[i]);
		i++;
	}
	return (bubble_sort_strarr(rtn));
}

void	print_export(char ***new_env)
{
	char	**to_print;
	int		i;

	i = 0;
	to_print = sort_strarr(*new_env);
	while (to_print[i])
	{
		printf("declare -x %s\n", to_print[i]);
		i++;
	}
	free_strrarr(to_print);
}

void	actually_set_variables(char **s_line, char ***new_env)
{
	int		i;
	char	**to_add;

	i = 1;
	while (s_line[i])
	{
		to_add = ft_split(s_line[i], '=');
		if (to_add[0] == NULL)
			printf("DunderSHell: export: `=': not a valid identifierr\n");
		else if (to_add[1] != NULL)
		{
			to_add[0] = ft_strjoin(to_add[0], "=");
			set_variable(new_env, to_add[0], to_add[1]);
		}
		else if (to_add[1] == NULL)
		{
			to_add[0] = ft_strjoin(to_add[0], "=");
			set_variable(new_env, to_add[0], "");
		}
		free_strrarr(to_add);
		i++;
	}
}

void	mini_export(char **s_line, char ***new_env, bool *b_in)
{
	*b_in = true;
	if (s_line[1] == NULL)
		print_export(new_env);
	else
		actually_set_variables(s_line, new_env);
}

/*
	Function to use in unset
*/
static void	delete_variable(char ***env, char *var)
{
	int		i;
	int		j;
	char	**tmp;

	tmp = *env;
	i = strarr_len(*env);
	(*env) = ft_calloc(i, sizeof(char *));
	i = 0;
	j = 0;
	while (tmp[i])
	{
		if (ft_strncmp(tmp[i], var, ft_strlen(var)) != 0)
		{
			(*env)[j] = ft_strdup(tmp[i]);
			i++;
			j++;
		}
		else
			i++;
	}
	if (i != strarr_len(*env))
		free_strrarr(tmp);
}

/*peut etre un probleme a la ligne var_to_unset =
 path_to_starrr((*new_env), s_line[i]); (ancienne note)*/
void	mini_unset(char **s_line, char ***new_env, bool *built_in)
{
	char	*var_to_unset;
	int		i;

	*built_in = true;
	if (s_line[1] == NULL)
		printf("unset : not enough arguments\n");
	else
	{
		i = 1;
		while (s_line[i])
		{
			if(s_line[i] && s_line[i][0] == '=' && s_line[i][1] == '\0')
			{
				printf("Minishell: unset: \"=\": not a valid identifier\n");
				i++;
				continue;
			}
			var_to_unset = return_variable((*new_env), s_line[i]);
			if (var_to_unset == NULL)
				i++;
			else
			{
				delete_variable(new_env, s_line[i]);
				i++;
			}
		}
	}
}

/* lol */
void	exit_was_too_long(char **s_line)
{
	int	i;

	if (s_line[1] == NULL)
	{
		printf("exit\n");
		rl_clear_history();
		exit (0);
	}
	i = 0;
	while(s_line[1][i])
	{
		if (s_line[1][i] < '0' || s_line[1][i] > '9')
		{
			printf("exit\n");
			printf("Dundershell: exit: %s: numeric argument required\n", s_line[1]);
			rl_clear_history();
			exit (255);
		}
		i++;
	}
}

/*
	étrangement quand je free line et s_line j'ai un leak mais 
	le leak part quand je ne les free pas ; je devrais vérifier pourquoi bientôt
*/
void	mini_exit(char *line, char **s_line, bool *b_in)
{
	(void)line;
	int tmp;
	int i;

	i = 1;
	*b_in = true;
	while(s_line[i++]);
	if (i > 3)
	{
		printf("Dundershell: exit: too many arguments\n");
		return;
	}
	exit_was_too_long(s_line);
	tmp = ft_atoi(s_line[1]);
	printf("exit\n");
	rl_clear_history();
	exit (tmp);
}

void	mini_dollar(char **s_line, char ***new_env, bool *b_in)
{
	char	*to_print;
	char	**splitted;

	*b_in = true;
	to_print = return_variable(*new_env, s_line[1]);
	if (to_print)
	{
		splitted = ft_split(to_print, '=');
		printf("%s\n",splitted[1]);
		free_strrarr(splitted);
	}
}

void	look_for_builtins(char **line, char ***s_line, char ***new_env, bool *b_in)
{
	if (ft_strncmp(*s_line[0], "echo", 5) == 0)
		mini_echo(*s_line, b_in);
	else if (ft_strncmp(*s_line[0], "cd", 3) == 0)
		mini_cd(*s_line, (new_env), b_in);
	else if (ft_strncmp(*s_line[0], "export", 8) == 0)
		mini_export(*s_line, (new_env), b_in);
	else if (ft_strncmp(*s_line[0], "unset", 6) == 0)
		mini_unset(*s_line, new_env, b_in);
	else if (ft_strncmp(*s_line[0], "pwd", 4) == 0)
		mini_pwd(b_in);
	else if (ft_strncmp(*s_line[0], "env", 5) == 0)
		mini_env((*new_env), b_in);
	else if (ft_strncmp(*s_line[0], "exit",5) == 0)
		mini_exit(*line, *s_line, b_in);
	else if (ft_strncmp(*s_line[0], "$", 1) == 0)
		mini_dollar(*s_line, new_env, b_in);
}
