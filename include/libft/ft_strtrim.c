/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 13:01:28 by pirichar          #+#    #+#             */
/*   Updated: 2021/09/24 10:21:15 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	char			*str;
	unsigned int	start;
	size_t			end;
	int				i;

	start = 0;
	i = 0;
	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1);
	while (s1[i] && ft_strchr(set, *(s1 + i)))
	{
		i++;
		start++;
	}
	while (end > start && ft_strchr(set, *(s1 + end - 1)))
		end--;
	str = ft_substr(s1, start, (end - start));
	return (str);
}
