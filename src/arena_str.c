/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:47:32 by pirichar          #+#    #+#             */
/*   Updated: 2024/07/25 11:47:32 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief 
 * 
 * @param arena 
 * @param size 
 * @return t_arena* 
 */
t_arena	*arena_init(t_arena *arena, size_t size)
{
	*arena = (t_arena){0};
	arena->block = (char *)ft_calloc(size, sizeof(char));
	arena->size = size;
	return (arena);
}

static char	*ft_fill_word_arena(const char *s, int *pos, char c)
{
	char	*rtn;
	int		i;
	int		start;
	int		end;

	i = *pos;
	while (s[i] && s[i] == c)
		i++;
	start = i;
	while (s[i] && s[i + 1] != c)
		i++;
	end = i;
	*pos = i + 1;
	rtn = arena_alloc(&g_ex.arena, sizeof(char) * (end - start + 2));
	if (!rtn)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		rtn[i] = s[start];
		i++;
		start++;
	}
	rtn[i] = '\0';
	return (rtn);
}

char	**ft_split_arena(const char *s, char c)
{
	char	**rtn;
	int		w_count;
	int		pos;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	pos = 0;
	w_count = ft_w_counts(s, c);
	rtn = arena_alloc(&g_ex.arena, sizeof(char *) * (w_count + 1));
	if (!rtn)
		return (NULL);
	while (i < w_count)
	{
		rtn[i] = ft_fill_word_arena(s, &pos, c);
		i++;
	}
	rtn[i] = NULL;
	return (rtn);
}

char	*ft_strjoin_arena(const char *s1, const char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = arena_alloc(&g_ex.arena,
			sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
