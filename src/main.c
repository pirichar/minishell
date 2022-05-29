/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 10:06:15 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/29 14:57:53 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && (unsigned char)s1[i] == (unsigned char)s2[i]
		&& i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print_env()
{
	char	*tmp;


}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char *line;
	char	*tmp;
	int		i;

	i = 0;
	while(1)
	{
		line = readline("PLR_ZSH: ");
		
		if (ft_strncmp(line, "env",5) == 0)
		{
			i = 0;
			while(env[i])
			{
				printf("%s\n",env[i]);
				i++;
			}
			printf("\n");
			free(line);
		}
		else if(ft_strncmp(line, "exit",5) == 0)
		{
			free(line);
			return (0);
		}
		else
			free(line);
	}
}