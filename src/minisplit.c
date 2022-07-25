#include "../include/minishell.h"

int	cnt_alloc(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (c != 34 && c != 39)
		c = ' ';
	if (c == 34)
		i++;
	while (str[i] && str[i++] != c)
		count++;
	if (c == 39)
		count += 2;
	return (count);
}

char	*split_quotes(char **str)
{
	char	*s;
	int		count;
	int		i;

	count = cnt_alloc(*str, **str);
	s = malloc(sizeof(char) * (count + 1));
	if (**str == '"')
		(*str)++;
	i = 0;
	while (count--)
	{
		s[i] = **str;
		i++;
		(*str)++;
	}
	if (**str == '"')
		(*str)++;
	s[i] = '\0';
	return (s);
}

char	*split_delims(char **str, char c)
{
	char	*s;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (*str[count] && *str[count] == c)
		count++;
	s = malloc(sizeof(char) * (count + 1));
	while (count--)
	{
		s[i] = **str;
		i++;
		(*str)++;
	}
	s[i] = '\0';
	return (s);
}

char	*split_words(char **str)
{
	char	*s;
	int		count;
	int		i;

	count = cnt_alloc(*str, **str);
	i = 0;
	s = malloc(sizeof(char) * (count + 1));
	while (count--)
	{
		s[i] = **str;
		i++;
		(*str)++;
	}
	s[i] = '\0';
	if (**str && **str == 34 || **str == 39)
		return(ft_strjoin(s, split_quotes(str)));
	// if (**str == 0 || **str == ' ' || **str == '|' || **str == '<' || **str == '>')
	return (s);
}

char **joinsplit(char **old, char **new)
{
	int		i;
	char	**tkns;

	if (!(*new) || !new)
		return (old);
	i = 0;
	while (old[i] != NULL)
		i++;
	tkns = malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (old[++i])
		tkns[i] = old[i];
	tkns[i] = *new;
	tkns[i + 1] = NULL;
	// free (old);
	return (tkns);
}

char	**split_tokens(char *str)
{
	char	*tmp;
	char	**ret;

	ret = NULL;
	while (*str != '\0')
	{
		tmp = NULL;
		// printf("here");
		if (*str && (*str == 39 || *str == 34))
		{
			tmp = split_quotes(&str);
			while (*str && (*str != ' ' && *str != '<' && *str != '>' && *str != '|'))
				tmp = ft_strjoin(tmp, split_quotes(&str));
			//check particularities of ft_strjoin to adapt to tkns
		}
		else if (*str && (*str == '<' || *str == '>' || *str == '|'))
			tmp = split_delims(&str, *str);
		else if (*str)
			tmp = split_words(&str);
		if (tmp)
			ret = joinsplit(ret, &tmp);
	}
	return (ret);
}

// int main(void)
// {
// 	char str[] = "<<";
// 	char **tkns;

// 	tkns = split_tokens(str);
// }