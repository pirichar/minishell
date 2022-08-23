#include "../include/minishell.h"


//checker les char des larray de la matrix, si une quote, et que closed, bool == true,
//(retour de check if closed, position de la quote de ferm, ou 0 si non fermer), 
// if bool == true, skip les delims, juska la quote de fermerture
// appliquer les cnt++ si un delim du set

int	check_if_close(char *string, int start)
{
	char	quote;
	int		i;

	i = start;
	quote = string[i++];
	while (string[i])
	{
		if (string[i] == quote)
			return (i);
		i++;
	}
	return (0);
}

int	cnt_actual_tkns(char **matrix, char *set)
{
	int			actual_cnt;
	t_indexes	index;

	init_index(&index);
	actual_cnt = 0;
	while (matrix[index.i])
	{
		while (matrix[index.i][index.j])
		{
			if (matrix[index.i][index.j] == '"' || matrix[index.i][index.j] == '\'')
			{
				if (check_if_close(matrix[index.i], index.j) != 0)
				{
					index.j = check_if_close(matrix[index.i], index.j);
					printf("quotes = %s j = %d tkn %d\n", matrix[index.i], index.j, actual_cnt);
				}
			}
			else if (matrix[index.i][index.j] == '>')
			{
				if (matrix[index.i][index.j + 1] != '\0')
				{
					printf("index j _ 1 %c\n", matrix[index.i][index.j + 1]);
					actual_cnt += 2;
				}
			}
			index.j++;
		}
		actual_cnt++;
		printf("no quote = %s j = %d tkn = %d\n", matrix[index.i], index.j, actual_cnt);
		index.j = 0;
		index.i++;
	}
	return (actual_cnt);
}

char	**split_with_set(char *string, char *set)
{
	char		**return_matrix;
	char		**temp_matrix;
	char		quotes;
	bool		closed;
	int			actual_cnt;

	return_matrix=NULL;
	temp_matrix = ft_split2(string, ' ');
	actual_cnt = cnt_actual_tkns(temp_matrix, set);
	printf("actual tkn = %d\n", actual_cnt);
	return (return_matrix);
}

int main(int argc, char const *argv[])
{
	char **retour;
	char *line;

	while (1)
	{
		line = calloc(10000, sizeof(char));
		read(1, line, 100000);
		retour = split_with_set(line, "<>|");
		free(line);
	}
	int k = 0;
	while (retour[k])
	{
		free(retour[k]);
		k++;
	}
	free(retour);
	return 0;
}