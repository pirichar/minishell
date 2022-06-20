#include "../include/minishell.h"

int	counttokens(const char *s)
{
	int		count;
	int		i;
	char	c;

	count = 0;
	i = 0;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] && (s[i] == 34 || s[i] == 39))
		{
			c = s[i];
			if (i == 0 || s[i - 1] == ' ' || s[i - 1] == c)
				count++;
			i++;
			while (s[i] && s[i] != c)
				i++;
			if (!s[i])
				return (-1);
			i++;
		}
		while (s[i] && s[i] == ' ')
			i++;
		if (s[i] && (i == 0 || s[i - 1] == ' ') && s[i] != 34 && s[i] != 39)
			count++;
		while (s[i] && s[i] != ' ' && s[i] != 34 && s[i] != 39)
			i++;
	}
	return (count);
}

char	*fillstr(const char *s, char c, int *i)
{
	char	*str;
	int		len;
	int		j;

	len = 0;
	j = 0;
	while (s[len] && s[len] != c)
		len++;
	// printf("%c", c);
	str = malloc(sizeof(char) * (++len));
	if (c == 34 || c == 39)
		str[j++] = c;
	while (s[*i] && s[*i] != c)
	{
		str[j] = s[*i];
		j++;
		(*i)++;
	}
	if (c == 34 || c == 39)
		str[j] = c;
	str[++j] = '\0';
	(*i)++;
	return (str);
}

char	**split(const char *s)
{
	int		count;
	int		i;
	int		x;
	char	c;
	char	**str_arr;

	count = counttokens(s);
	if (count == -1)
	{
		write(2, "error: missing a quote\n", 24);
		return (NULL);
	}
	str_arr = malloc(sizeof(char *) * (count + 1));
	i = 0;
	x = 0;
	while (count--)
	{
		c = ' ';
		while (s[i] && s[i] == ' ')
			i++;
		if (s[i] && (s[i] == 34 || s[i] == 39))
			c = s[i++];
		str_arr[x] = fillstr(s, c, &i);
		// printf("%d\n", i);
		x++;
	}
	str_arr[x] = NULL;
	return (str_arr);
}

// int	main(void)
// {
// 	int	i;

// 	i = -1;
// 	char str[] = "' hel\"lo'";
// 	char **token = split(str);
// 	while (token[++i] != NULL && token != NULL)
// 		printf("%s\n", token[i]);
	
// }
