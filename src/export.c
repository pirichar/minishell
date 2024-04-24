#include "../include/minishell.h"

char	**bubble_sort_strarr(char **rtn)
{
	int		i;
	char	*tmp;

	i = 0;
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
			to_add[0] = ft_strjoin_free(to_add[0], "=");
			set_variable(new_env, to_add[0], to_add[1]);
		}
		else if (to_add[1] == NULL)
		{
			to_add[0] = ft_strjoin_free(to_add[0], "=");
			set_variable(new_env, to_add[0], "");
		}
		free_strrarr(to_add);
		i++;
	}
}

void	mini_export(char **s_line, char ***new_env, t_parsing *parse)
{
	parse->b_in = true;
	if (s_line[1] == NULL)
		print_export(new_env);
	else
		actually_set_variables(s_line, new_env);
}
