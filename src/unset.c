#include "../include/minishell.h"

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
void	mini_unset(char **s_line, char ***new_env, t_parsing *parse)
{
	char	*var_to_unset;
	int		i;

	parse->b_in = true;
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