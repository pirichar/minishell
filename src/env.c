/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:43:29 by pirichar          #+#    #+#             */
/*   Updated: 2024/07/25 11:43:30 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Basically just go through all the new_env and print everything
 * 
 * @param new_env The new env to print
 * @param parse to set the b_in to true
 */
void	mini_env(char **new_env, t_parsing *parse)
{
	int		i;
	char	**tmp;

	parse->b_in = true;
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

/**
 * @brief Helper function called in export.c by bubble_sort_strarr
			Here since it was not in the libft, should be there
 * 
 * @param s1 to cmpr 
 * @param s2 to cmpr
 * @return int 
  // TO-DO MOVE TO LIBFT
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/**
 * @brief UNUSED FUNCTION 
 * 
 * @param to_print 
 // TO-DO To remove
 */
void	print_out_dir(char **to_print)
{
	int	i;

	i = 0;
	to_print = bubble_sort_strarr(to_print);
	while (to_print[i])
		printf("%s ", to_print[i++]);
}
