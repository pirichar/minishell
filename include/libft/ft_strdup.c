/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 10:46:01 by pirichar          #+#    #+#             */
/*   Updated: 2021/09/27 09:52:32 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* DESCRIPTION
 * The strdup() function allocates sufficient memory for a copy of the string
 * s1, does the copy, and returns a pointer to it.  The pointer may subsequently
 * be used as an argument to the function free(3).
 * If insufficient memory is available, NULL is returned and errno is set to
 * ENOMEM*/

char	*ft_strdup(const char *s1)
{
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (str == NULL)
	{
		return (0);
	}
	ft_strlcpy(str, s1, sizeof(char) * (ft_strlen(s1) + 1));
	*(str + ft_strlen(s1)) = '\0';
	return (str);
}
