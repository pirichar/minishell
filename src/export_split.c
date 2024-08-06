/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 08:48:04 by pirichar          #+#    #+#             */
/*   Updated: 2024/07/02 14:20:28 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*allocate_word(int start, int end, const char *s)
{
	char	*rtn;
	int		i;

	rtn = malloc(sizeof(char) * (end - start + 2));
	if (!rtn)
		return (NULL);
	i = 0;
	while (start <= end)
		rtn[i++] = s[start++];
	rtn[i] = '\0';
	return (rtn);
}

static int	find_split_position(const char *s, int *pos, char c)
{
	int	i;
	int	first_equal;

	i = *pos;
	first_equal = 1;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c && first_equal)
		{
			first_equal = 0;
			break ;
		}
		i++;
	}
	*pos = i + 1;
	return (i);
}

static char	*ft_fill_word_exp(const char *s, int *pos, char c)
{
	int	start;
	int	end;

	start = *pos;
	end = find_split_position(s, pos, c) - 1;
	return (allocate_word(start, end, s));
}

char	**ft_export_split(const char *s, char c)
{
	char	**rtn;
	int		pos;
	int		i;

	if (!s)
		return (NULL);
	rtn = malloc(sizeof(char *) * 3);
	if (!rtn)
		return (NULL);
	pos = 0;
	i = 0;
	while (i < 2)
		rtn[i++] = ft_fill_word_exp(s, &pos, c);
	rtn[i] = NULL;
	return (rtn);
}
