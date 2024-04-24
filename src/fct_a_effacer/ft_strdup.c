#include "../include/minishell.h"

/* DESCRIPTION
 * The strdup() function allocates sufficient memory for a copy of the string
 * s1, does the copy, and returns a pointer to it.  The pointer may subsequently
 * be used as an argument to the function free(3).
 * If insufficient memory is available, NULL is returned and errno is set to
 * ENOMEM*/

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		num;

	str = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (str == NULL)
	{
		return (0);
	}
	num = ft_strlcpy(str, s1, sizeof(char) * (ft_strlen(s1) + 1));
	*(str + ft_strlen(s1)) = '\0';
	return (str);
}
