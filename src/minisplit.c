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
	printf("count : %d\n", count);
	return (count);
}

// char	*fillstr(const char *s, char c, int *i)
// {
// 	char	*str;
// 	int		len;
// 	int		j;

// 	len = 0;
// 	j = 0;
// 	while (s[len] && (c == ' ' || s[len] != ' '))
// 	{
// 		while (s[len] && s[len] != c)
// 			len++;
// 		printf("%d", len);
// 	}
// 	str = malloc(sizeof(char) * (++len));
// 	while (len-- > 0)
// 	{
// 		if (s[*i] == 34 || s[*i] == 39)
// 			c = s[*i];
// 		// printf("%c", c);
// 		if (c == 34 || c == 39)
// 			str[j++] = c;
// 		while (s[*i] && s[*i] != c)
// 		{
// 			str[j] = s[*i];
// 			j++;
// 			(*i)++;
// 		}
// 		if (c == 34 || c == 39)
// 			str[j] = c;
// 	}
// 	str[++j] = '\0';
// 	(*i)++;
// 	return (str);
// }

int len_count(const char *s, int i)
{
	char	c;
	int		x;
	int 	count;

	count = 0;
	while (s[i])
	{
		c = ' ';
		if (s[i] == 34 || s[i] == 39)
			c = s[i];
		x = 0;
		while (s[i] && (s[i++] != c || x++ == 0))
			count++;
		if (c == 34 || c == 39)
			count++;
		// printf("'%c'\n", s[i]);
		if (s[i] && s[i] == ' ')
			break;
	}
	// printf("lencount : %d\n", count);
	return (count + 1);	
}

char	*fill(const char *s, int *i)
{
	char	*str;
	char	c;
	int		x;
	int		j;

	j = 0;
	c = ' ';
	if (s[*i] == 34 || s[*i] == 39)
		c = s[*i];
	// printf("position : %c\n", *s);
	str = ft_calloc(len_count(s, *i), sizeof(char));
	while (s[*i])
	{
		c = ' ';
		if (s[*i] == 34 || s[*i] == 39)
			c = s[*i];
		x = 0;
		while (s[*i] && (s[*i] != c || x++ == 0))
			str[j++] = s[(*i)++];
		// if (c == 34 || c == 39)
		// 	str[j++] = c;
		// printf("'%c'\n", s[*i]);
		// printf(" ----- \"%c\" -------", s[*i]);
		if (s[*i] && s[*i] == ' ')
			break;
	}
	str[j] = '\0';
	printf("pos of null : %d\n", j);
	return (str);
}

char	**split(const char *s)
{
	int		count;
	int		i;
	int		x;
	char	**str_arr;


	count = counttokens(s);
	if (count == -1)
	{
		write(2, "error: missing a quote\n", 24);
		return (NULL);
	}
	str_arr = ft_calloc((count + 1), sizeof(char *));
	i = 0;
	x = 0;
	while (count--)
	{
		str_arr[x++] = fill(s, &i);
		i++;
	}
	str_arr[x] = NULL;
	return (str_arr);
}

// int	main(void)
// {
// 	int	i;

// 	i = -1;
// 	char str[] = "'allo' toi";
// 	char **token = split(str);
// 	while (token != NULL && token[++i] != NULL)
// 		printf("%s\n", token[i]);
	
// }
