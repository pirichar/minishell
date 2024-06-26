#include "../include/minishell.h"
#include <stdbool.h>

/**
 * @brief Add new variable to the env ONLY CALLED BY SET_VARIABLE

 * @param env Pointer to the char** env 
 * @param var Variable to set
 * @param variable its value
 */
static void	add_new_variable(char ***env, char *var, char *value)
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
	(*env)[i] = ft_strjoin(var, value);
	free_strrarr(tmp);
}

/**
 * @brief Set or add a new variable with EXPORT popa=MOMAN
 * 
 * @param env env variables passed by pointer
 * @param var variable to set
 * @param new_var 
 */
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

/**
 * @brief 
 * 
 * @param s_line 
 * @param new_env 
 * @param parse 
 */
void	mini_dollar(char **s_line, char ***new_env, t_parsing *parse)
{
	char	*to_print;
	char	**splitted;

	parse->b_in = true;
	if (s_line[1] == NULL)
		return ;
	if (s_line[1][0] == '?' && s_line[1][1] == '\0')
	{
		if (parse->ex->cmd_rtn == 512)
			printf("127\n");
		else if (parse->ex->cmd_rtn != 0)
			printf("1\n");
		else
			printf("%d\n", parse->ex->cmd_rtn);
		return ;
	}
	to_print = return_variable(*new_env, s_line[1]);
	if (to_print)
	{
		splitted = ft_split(to_print, '=');
		printf("%s\n", splitted[1]);
		free_strrarr(splitted);
	}
}

/**
 * @brief Basically what the name of the function says , not bad eh?
			This function is called from execution functions
			Echo
			Cd
			Export
			Unset
			pwd
			env
			exit
			$
 * 
 * @param s_line Pointer to the Char** cmd
 * @param new_env the env whihc is needed in some builtins
 * @param parse  the parse structure so I can set builtin to true
 */
void	look_for_builtins(char ***s_line, char ***new_env, t_parsing *parse)
{
	if (ft_strncmp(*s_line[0], "echo", 5) == 0)
		mini_echo(*s_line, parse);
	else if (ft_strncmp(*s_line[0], "cd", 3) == 0)
		mini_cd(*s_line, (new_env), parse);
	else if (ft_strncmp(*s_line[0], "export", 8) == 0)
		mini_export(*s_line, (new_env), parse);
	else if (ft_strncmp(*s_line[0], "unset", 6) == 0)
		mini_unset(*s_line, new_env, parse);
	else if (ft_strncmp(*s_line[0], "pwd", 4) == 0)
		mini_pwd(parse);
	else if (ft_strncmp(*s_line[0], "env", 5) == 0)
		mini_env((*new_env), parse);
	else if (ft_strncmp(*s_line[0], "exit", 5) == 0)
		mini_exit(*s_line, parse);
	else if (ft_strncmp(*s_line[0], "$", ft_strlen(*s_line[0])) == 0)
		mini_dollar(*s_line, new_env, parse);
}
