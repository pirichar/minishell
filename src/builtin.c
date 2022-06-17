#include "../include/minishell.h"

int	strarr_len(char **str_arr)
{
	int i;

	i = 0;
	while(str_arr[i])
		i++;
	return (i);
}

void	free_strrarr(char **to_free)
{
	int i;

	i = 0;
	while(to_free[i])
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
	int i;
	int j;
	char **tmp;
	
	tmp = *env;
	i = strarr_len(tmp);
	(*env) = malloc(sizeof(char *) * i);
	(*env)[i] = 0;
	i = 0;
	j = 0;
	while(tmp[i])
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



void	add_new_variable(char ***env,char *var, char *variable)
{
	int i;
	char **tmp;
	tmp = *env; 
	i = strarr_len(*env);
	(*env) = ft_calloc(i + 2, sizeof(char *));
	i = 0;
	while(tmp[i])
	{
		(*env)[i] = ft_strdup(tmp[i]);
		i++;
	}
	(*env)[i] = ft_strjoin(var, variable);
	free_strrarr(tmp);
}


void	set_variable(char ***env, char *var, char *new_var)
{
	int i;
	char *tmp;

	i = 0;
	while((*env) && (*env)[i])
	{
		if (ft_strncmp((*env)[i], var, ft_strlen(var)) == 0)
		{
			tmp = (*env)[i];
			(*env)[i] = ft_strjoin(var, new_var);
			free(tmp);
			break;
		}
		i++;
	}
	if ((*env)[i] == NULL)
			add_new_variable(env, var, new_var);
}

void	mini_cd(char **s_line, char **new_env)
{
	/*change the OLDPWD= folder*/
	char *actual_pwd;
	char *buff;
	
	buff = NULL;
	actual_pwd = getcwd(buff, 1024);
	set_variable(&new_env, "OLDPWD=", actual_pwd);
	free(actual_pwd);
	free(buff);
	chdir(s_line[1]);
	/*change the PWD*/
	buff = NULL;
	actual_pwd = getcwd(buff, 1024);
	set_variable(&new_env, "PWD=", actual_pwd);
	free(actual_pwd);
	free(buff);
}
//s'assurer que dans la version officielle echo "-n" 
// fonctionne aussi mais pas echo " -n"
void	mini_echo(char **s_line)
{
	int		i;
	bool	with_nl;

	i = 1;
	with_nl = true;
	while (s_line[i])
	{
		//filter un nombre inifni de -n
		//fitrer un nombre infini de n dans le flag -n
		//-n had to be at the start
		if (ft_strncmp(s_line[1], "-n", 3) == 0)
		{
			with_nl = false;
			i++;
		}
		if (s_line[i] != 0)
			printf("%s", s_line[i++]);
	}
	if (with_nl)
		printf("\n");
}


void	mini_pwd()
{
	char *to_print;
	char *buff;
	
	buff = NULL;
	to_print = getcwd(buff, 1024);
	printf("%s\n",to_print);
	free(to_print);
	free(buff);
}

void	mini_env(char **new_env)
{
	int i;
	char **tmp;

	i = 0;
	while(new_env[i])
	{
		tmp = ft_split(new_env[i], '=');
		if (tmp[1] != NULL)
			printf("%s\n",new_env[i]);
		free_strrarr(tmp);
		i++;
	}
}
char **	sort_strarr(char **to_sort)
{
	int i;
	int j;
	char **rtn;
	char *tmp;
	
	i = 0;
	while(to_sort && to_sort[i])
		i++;
	rtn = malloc(sizeof(char *) * (i + 1));
	rtn[i + 1] = 0;
	i = 0;
	while(to_sort[i])
	{
		rtn[i] = ft_strdup(to_sort[i]);
		i++;
	}
	i = 0;
	j = 0;
	while(rtn[i+1])
	{
		if (ft_strncmp(rtn[i], rtn[i+1], ft_strlen(rtn[i])) > 1)
		{
			tmp = rtn[i];
			rtn[i] = rtn[i+1];
			rtn[i+1] = tmp;
			i = 0;
		}
		else
			i++;
	}
	return (rtn);
}

void	look_for_builtins(char **s_line, char ***new_env, bool *b_in)
{
	if(ft_strncmp(s_line[0], "echo",5) == 0)
	{
		*b_in = true;
		mini_echo(s_line);
	}
	else if(ft_strncmp(s_line[0], "cd",3) == 0)
	{
		*b_in = true;
		mini_cd(s_line, (*new_env));
	}
	else if(ft_strncmp(s_line[0], "export",ft_strlen("export")) == 0)
	{
		*b_in = true;
		char **to_add;
		int i;

		i = 0;
		//if export alone
		if (s_line[1] == NULL)
		{
			//copy new_env into a new memory space and put it in alphabetical order
			to_add = sort_strarr(*new_env);
			while(to_add[i])
			{
				printf("declare -x %s\n", to_add[i]);
				i++;
			}
			free(to_add);
		}
		else
		{
			i = 1;
			while(s_line[i])
			{
				to_add = ft_split(s_line[i], '=');
				if (to_add[1] != NULL)
				{
					to_add[0] = ft_strjoin(to_add[0], "=");
					set_variable(new_env, to_add[0], to_add[1]);
				}
				else
				{
					to_add[0] = ft_strjoin(to_add[0], "=");
					set_variable(new_env, to_add[0], "");	
				}
				free (to_add);
				i++;
			}
		}
	}
	else if(ft_strncmp(s_line[0], "unset",6) == 0)
	{
		char **var_to_unset;
		*b_in = true;
		int i;

		if (s_line[1] == NULL)
			printf("unset : not enough arguments\n");
		else
		{
			i = 1;
			while(s_line[i])
			{
				var_to_unset = var_to_strarr((*new_env), s_line[i]);
				if(var_to_unset == NULL)
					i++;
				else
				{
					delete_variable(new_env, s_line[i]);
					i++;
				}
			}
		}

	}
	else if(ft_strncmp(s_line[0], "pwd",4) == 0)
	{
		*b_in = true;
		mini_pwd();
	}
	else if (ft_strncmp(s_line[0], "env",5) == 0)
	{
		*b_in = true;
		mini_env((*new_env));
	}
}