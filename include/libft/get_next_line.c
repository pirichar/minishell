/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:19:30 by pirichar          #+#    #+#             */
/*   Updated: 2024/07/03 23:50:12 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_file(int fd, char *saved, char **new_line)
{
	char			buff[BUFFER_SIZE + 1];
	ssize_t			ret;
	char			*tmp;

	ret = BUFFER_SIZE;
	while (ret == BUFFER_SIZE)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret == -1)
			return (NULL);
		buff[ret] = '\0';
		if (saved == NULL)
			saved = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(saved, buff);
			free (saved);
			saved = tmp;
		}
		*new_line = ft_strchr(saved, '\n');
		if (*new_line)
			break ;
	}
	return (saved);
}

char	*get_next_line(int fd)
{
	static char		*saved;
	char			*rtn;
	char			*new_line;

	if (fd < 0)
		return (NULL);
	saved = read_file(fd, saved, &new_line);
	if (saved == NULL)
		return (NULL);
	if (new_line)
	{
		rtn = ft_substr(saved, 0, (new_line - saved + 1));
		saved = free_stuff(saved, new_line);
	}
	else
	{
		rtn = saved;
		saved = NULL;
		if (!*rtn)
		{
			free(rtn);
			rtn = NULL;
		}
	}
	return (rtn);
}

char	*free_stuff(char *saved, char *new_line)
{
	char	*tmp;

	tmp = ft_substr(new_line, 1, ft_strlen(new_line));
	free(saved);
	saved = tmp;
	return (saved);
}