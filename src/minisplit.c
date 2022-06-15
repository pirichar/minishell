#include "../include/minishell.h"

bool	even_quotes(const char *s)
{
	int	i;
	int single;
	int dbl;

	i = -1;
	while(s[++i])
	{
		if (s[i] == 34)
			dbl++;
		if (s[i] == 39)
			single++;
	}
	if ((dbl % 2) != 0 || (single % 2) != 0)
		return (false);
	return (true);
}

int	counttokens(const char *s)
{
	int		count;
	int		i;
	char	c;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] && (s[i] == 34 || s[i] == 39) && (i == 0 || s[i - 1] == ' '))
		{
			printf("jdsah");
			c = s[i];
			i++;
			while (s[i] && s[i] != c)
				i++;
			count++;
		}
		if (!s[i])
			return (-1);
		i++;
		while (s[i] && s[i] == ' ')
			i++;
		if (s[i] && s[i] != ' ' /*&& (s[i] != 34 && s[i] != 39)*/)
			count++;
		while (s[i] && s[i] != ' ' /*&& (s[i] != 34 && s[i] != 39)*/)
			i++;
	}
	return (count);
}

char	**split(const char *s)
{
	int count;

	closed = even_quotes(s);
	count = counttokens(s);
}

int	main(void)
{
	char str[] = "hello 'w'or'ld";
	printf("%d\n", split(str)[i]);
}
