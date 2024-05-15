#include "../include/minishell.h"

t_tkns	*make_node(char *s)
{

	t_tkns	*new;
	new = malloc(sizeof(t_tkns));
	if (new == NULL)
		return (NULL);
	new->data = ft_strjoin(*s, s[1]);
	new->next = NULL;
	return (new);
}

t_tkns *new_split(char *s, char *set) // make shorter
{
	t_tkns	*matrix;
	t_tkns	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	matrix = malloc(sizeof(t_tkns));
	if (matrix == NULL)
		return (NULL);
	while (*s)
	{
		if (ft_strchr(set, *s))
		{

			if ((*s == '<' || *s == '>') && s[1]  == *s)
			{
				new = make_node(s);
				if (!matrix->data)
					matrix = new;
				else
					matrix->next = new;
				matrix = new;
				set_toktype(matrix); //a faire
				s += 2;
			}
			else if (*s == '<' || *s == '>' || *s == '|')			
			{
				new = make_node(s);
				if (!matrix->data)
					matrix = new;
				else
					matrix->next = new;
				matrix = new;
				set_toktype(matrix); //a faire
				s += 1;
			}
			if (*s != '<' || *s != '>' || *s != '|')
			{
				new = malloc(sizeof(t_tkns));
				if (new == NULL)
					return (NULL);
				while ((*s != '<' || *s != '>' || *s != '|'))
				{
					new->data[i] = *s;
					s++;
					i++;
				}
				new->data[i] = '\0';
				new->next = NULL;
				if (!matrix->data)
					matrix = new;
				else
					matrix->next = new;
				matrix = new;
			}
		}
		s++;
	}
	return matrix;
}