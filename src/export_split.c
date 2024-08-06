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

// Allocates memory and creates a string from the given range in `s`
// from `start` to `end`.
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

// Extracts the key portion of the string,
// which is everything before the first '='.
// Updates `pos` to the character after the '='.
static char	*ft_extract_key(const char *s, int *pos, char c)
{
	int		start;
	int		end;

	start = *pos;
	while (s[*pos] && s[*pos] != c)
		(*pos)++;
	end = *pos;
	if (s[*pos] == c)
		(*pos)++;
	return (allocate_word(start, end - 1, s));
}

// Extracts the value portion of the string,
///which is everything after the first '='.
// Uses the current position in `pos` to start extracting.
static char	*ft_extract_value(const char *s, int *pos)
{
	int		start;

	start = *pos;
	while (s[*pos])
		(*pos)++;
	return (allocate_word(start, *pos - 1, s));
}

// Splits the input string `s` into a key-value pair based on the first '='.
// Returns a 2-element array where the first element is the key and the
// second element is the value, even if the value contains '='.
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
	rtn[i++] = ft_extract_key(s, &pos, c);
	rtn[i++] = ft_extract_value(s, &pos);
	rtn[i] = NULL;
	return (rtn);
}
