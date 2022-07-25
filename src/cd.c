#include "../include/minishell.h"

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
