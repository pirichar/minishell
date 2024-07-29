/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandrinedube <alexandrinedube@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:36:15 by adube             #+#    #+#             */
/*   Updated: 2024/07/29 16:34:46 by alexandrine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ret_value(char *s1, char *s2, t_parsing *p_l)
{
	char	*str;
	char	*num;
	int		i;
	int		y;

	i = 0;
	y = 0;
	if (s2[p_l->index] != '\0' && s2[p_l->index + 1] == '?')
	{
		str = arena_alloc(&g_ex.arena, MAX_INPUT);
		num = ft_itoa(g_ex.status);
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
		while (num[y])
			str[i++] = num[y++];
		free(num);
		p_l->new_i = i;
		p_l->index += 2;
		return (str);
	}
	return (s1);
}
