#include "../include/minishell.h"

/*
	Basically just go through all the new_env and print everything
*/
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

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	print_out_dir(char **to_print)
{
	int	i;

	i = 0;
	to_print = bubble_sort_strarr(to_print);
	while (to_print[i])
		printf("%s ", to_print[i++]);
}
