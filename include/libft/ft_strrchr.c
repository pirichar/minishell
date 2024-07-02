/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 10:37:55 by pirichar          #+#    #+#             */
/*   Updated: 2021/09/16 14:13:31 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*rtn;
	int		i;

	i = ft_strlen(s);
	rtn = (char *)s;
	while (i >= 0)
	{
		if (rtn[i] == (char)c)
			return (&rtn[i]);
		else
			i--;
	}
	return (NULL);
}
