/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 18:00:02 by jvigneau          #+#    #+#             */
/*   Updated: 2022/07/21 11:12:40 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ecrire une fct qui retourne un tableau de chaines de char obtenu
// en separant s a laide de c comme delimitateur

#include "libft.h"
/*
static int	check_nb_tabs(const char *s, char c)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (s == 0)
		return (0);
	while (*s)
	{
		if (*s != c && k == 0)
		{
			i++;
			k = 1;
		}
		else if (*s == c)
			k = 0;
		s++;
	}
	return (i);
}

static char	*malloc_mot(const char *s, int start, int finish)
{
	char	*mot;
	int		i;

	i = 0;
	mot = ft_calloc((finish - start + 1), sizeof(char));
	if (!mot)
		return (NULL);
	while (start < finish)
		mot[i++] = s[start++];
	mot[i] = '\0';
	return (mot);
}

static char	**split(const char *s, char c, char **tabs)
{
	int		i;
	size_t	k;
	size_t	l;

	i = -1;
	k = 0;
	l = 0;
	while (s[k] && s[k] == c)
		k++;
	while (k <= ft_strlen(s))
	{
		if (s[k] != c && i < 0)
			i = k;
		else if ((s[k] == c || k == ft_strlen(s)) && i >= 0)
		{
			tabs[l++] = malloc_mot(s, i, k);
			i = -1;
		}
		k++;
	}
	tabs[l] = 0;
	return (tabs);
}

char	**ft_split(const char *s, char c)
{
	char	**tabs;

	tabs = malloc((check_nb_tabs(s, c) + 1) * sizeof(char *));
	if (s == 0)
	{
		*tabs = 0;
		return (tabs);
	}
	if (!tabs)
		return (NULL);
	return (split(s, c, tabs));
}*/

int	ft_w_counts(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (i == 0 && s[i] != c)
			count ++;
		else if (s[i] != c && s[i - 1] == c)
			count ++;
		i++;
	}
	return (count);
}

char	*ft_fill_word(const char *s, int *pos, char c)
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
	rtn = malloc(sizeof(char) * (end - start + 2));
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

char	**ft_split(const char *s, char c)
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
	rtn = malloc(sizeof(char *) * (w_count + 1));
	if (!rtn)
		return (NULL);
	while (i < w_count)
	{
		rtn[i] = ft_fill_word(s, &pos, c);
		i++;
	}
	rtn[i] = NULL;
	return (rtn);
}
