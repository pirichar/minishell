#include "../include/minishell.h"

/**
 * @brief Function used when there is no PWD
			it will only print out 
			the user followed by
			dunder shell
 * 
 * @param blue_user passed to join
 * @return sent to pwd_prompt
 */
static char	*pwd_not_there(char *blue_user)
{
	char	*pwd;
	char	*prompt;

	pwd = ft_strjoin(blue_user, "\e[1;31m@\e[1;32m");
	prompt = ft_strjoin(pwd, "/DunderShell $> \e[0m");
	free(pwd);
	free(blue_user);
	return (prompt);
}

/**
 * @brief Function designed by JR (old member of the team)
			This function will look for the PWD in the env
			If not found it will use pwd not there
			If found it will use the PWD to create the prompt
 * 
 * @param new_env used to search PWD
 * @param blue_user used to add to the prompt
 * @return string with pwd or not and user
 */
static char	*pwd_prompt(char *new_env[], char *blue_user)
{
	int		i;
	char	*user;
	char	*pwd;
	char	*with_at;
	char	*prompt;

	i = 0;
	while (ft_strncmp(new_env[i], "PWD=", 4))
	{
		i++;
		if (new_env[i] == NULL)
			return (pwd_not_there(blue_user));
	}
	user = calloc(ft_strlen(new_env[i]), sizeof(char));
	ft_strlcpy(user, new_env[i] + 4, ft_strlen(new_env[i]));
	with_at = ft_strjoin(blue_user, "\e[1;31m@\e[1;32m");
	pwd = ft_strjoin(user, " $> \e[0m");
	prompt = ft_strjoin(with_at, pwd);
	free(blue_user);
	free(with_at);
	free(pwd);
	free(user);
	return (prompt);
}

/**
 * @brief Function called to return a prompt to give to minishell
			Its called in main.c for ex->prompt
			or in ft_signals for the prompt in sigint
			It will use its local functions to
			Get the PWD if available
			Get the User if available
			If not available we just return DunderShell
 * 
 * @param new_env to look for USER and PWD
 * @return prompt returned
 */
char	*set_prompt(char *new_env[])
{
	char	*user;
	char	*blue_user;
	char	*prompt;
	int		i;

	i = 0;
	while (ft_strncmp(new_env[i], "USER=", 5))
	{
		i++;
		if (new_env[i] == NULL)
		{
			prompt = ft_strjoin("\e[1;32m", "DunderShell $> \e[0m");
			return (prompt);
		}
	}
	user = calloc(ft_strlen(new_env[i]), sizeof(char));
	ft_strlcpy(user, new_env[i] + 5, ft_strlen(new_env[i]));
	blue_user = ft_strjoin(BBLU, user);
	free(user);
	prompt = pwd_prompt(new_env, blue_user);
	return (prompt);
}
