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
	free_strrarr(tmp);
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

char *	return_variable(char ***env, char *var)
{
	int		i;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], var, ft_strlen(var)) == 0)
		{
			return (*env[i]);
		}
		i++;
	}
	return (NULL);
}

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
	while (s_line[*(i)] && ft_strncmp(s_line[*(i)], "-n", 2) == 0 && (*check_nl))
	{
		if (check_only_n(s_line[*(i)]))
			(*with_nl) = false;
		else
			break ;
		(*i)++;
	}
}

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
			return;
		check_nl = false;
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

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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

/*peut etre un probleme a la ligne var_to_unset =
 var_to_strarr((*new_env), s_line[i]); (ancienne note)*/
void	mini_unset(char **s_line, char ***new_env, bool *built_in)
{
	char	**var_to_unset;
	int		i;

	*built_in = true;
	if (s_line[1] == NULL)
		printf("unset : not enough arguments\n");
	else
	{
		i = 1;
		while (s_line[i])
		{
			var_to_unset = var_to_strarr((*new_env), s_line[i]);
			if (var_to_unset == NULL)
				i++;
			else
			{
				delete_variable(new_env, s_line[i]);
				i++;
			}
			free_strrarr(var_to_unset);
		}
	}
}

/* lol */
void	exit_was_too_long(char **s_line)
{
	int i;

	if (s_line[1] == NULL)
	{
		printf("exit\n");
		exit (0);
	}
	i = 0;
	while(s_line[1][i])
	{
		if (s_line[1][i] < '0' || s_line[1][i] > '9')
		{
			printf("Dundershell: exit: %s: numeric argument required\n", s_line[1]);
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
	exit (tmp);
}

void	mini_dollar(char **s_line, char ***new_env, bool *b_in)
{
	*b_in = true;
	if (return_variable(new_env, s_line[1]) != NULL)
		printf("%s\n",return_variable(new_env, s_line[1]));
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
