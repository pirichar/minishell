#include "../include/minishell.h"
/*
	Function to use in unset
*/
// static void	delete_variable(char **env, char *var, char *variable)
// {
// 	int i;
// 	int j;
// 	char **tmp;
	
// 	tmp = env;
// 	i = strarr_len(tmp);//strlen of old tmp
// 	env = malloc(sizeof(char *) * i ); //malloc array 1 smaller then the last one (with no + 1)
// 	env[i] = 0;
// 	i = 0;
// 	j = 0;
// 	while(tmp[i])//pass over all the tmp character and filter the one you don't want
// 	{
// 		if (ft_strncmp(tmp[i], var, ft_strlen(var)) == 0)
// 			i++;
// 		env[j] = ft_strdup(tmp[i]);
// 		i++;
// 		j++;
// 	}
// 	env[i] = ft_strjoin(var, variable);
// 	free_strrarr(tmp);
// }

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

void	add_new_variable(char ***env,char *var, char *variable)
{
	int i;
	char **tmp;
	 //env pointe vers mon env 
	tmp = *env; // tmp pointe vers env
	i = strarr_len(*env);
	printf("this is i %d\n", i);
	(*env) = ft_calloc(i+ 2, sizeof(char *));
	i = 0;
	while(tmp[i])
	{
		(*env)[i] = ft_strdup(tmp[i]);
		i++;
	}
	// printf("This is i [%d] before to add the value of the new variable [%s]\n", i, (*env)[i]);
	(*env)[i] = ft_strjoin(var, variable);
	// printf("this is env[%d] after we did the str_join = [%s]",i, (*env)[i]);
	// i = 0;
	// while((*env)[i])
	// {
	// 	printf("%s\n",(*env)[i]);
	// 	i++;
	// }
	free_strrarr(tmp);
}


void	set_variable(char ***env, char *var, char *new_var)
{
	int i;
	char *tmp;

	i = 0;
	while((*env)[i])
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

	i = 0;
	while(new_env[i])
	{
		printf("%s\n",new_env[i]);
		i++;
	}
}

void	look_for_builtins(char **s_line, char **new_env, bool *b_in)
{

	if(ft_strncmp(s_line[0], "echo",5) == 0)
	{
		*b_in = true;
		mini_echo(s_line);
	}
	else if(ft_strncmp(s_line[0], "cd",3) == 0)
	{
		*b_in = true;
		mini_cd(s_line, new_env);
	}
	else if(ft_strncmp(s_line[0], "export",8) == 0)
	{
		*b_in = true;
		char **to_add;
		int i;

		i = 0;
		//if export alone
			//print out the list of env but alphabetically 
			//with something infront
		if (s_line[1] == NULL)
		{
			//copy new_env into a new memory space and put it in alphabetical order
			while(new_env[i])
			{
				printf("declare -x %s\n", new_env[i]);
				i++;
			}
		}
		else
		{
			to_add = ft_split(s_line[1], '=');
			to_add[0] = ft_strjoin(to_add[0], "=");
			set_variable(&new_env, s_line[0], s_line[1]);
		}
		//else
			//ft_split with = 
			//keep the = for the new_split[0]
			//add the content after the = to the new_split[1];
			//set_variable(env, new_split[0], new_split[1]);
	}
	else if(ft_strncmp(s_line[0], "unset",6) == 0)
	{
		*b_in = true;
		//if no command just show all the Standard variables
	}
	else if(ft_strncmp(s_line[0], "pwd",4) == 0)
	{
		*b_in = true;
		mini_pwd();
	}
	else if (ft_strncmp(s_line[0], "env",5) == 0)
	{
		*b_in = true;
		mini_env(new_env);
	}
}