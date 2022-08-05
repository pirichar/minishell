#include "../include/minishell.h"


int	get_nb_items_in_folder(void)
{
	DIR				*dir;
	struct dirent	*sd;
	int				i;

	i = 0;
	dir = opendir(".");
	if (dir == NULL)
	{
		printf("error ! Unable to open directory\n");
		return (-1);
	}
	while ((sd = readdir(dir)) != NULL)
	{
		if (*sd->d_name
			&& (ft_strncmp(sd->d_name, ".", ft_strlen(sd->d_name)) != 0)
			&& (ft_strncmp(sd->d_name, "..", ft_strlen(sd->d_name)) != 0))
			i++;
	}
	closedir(dir);
	return (i);
}

int	get_nb_items_chars_in_folder(void)
{
	DIR				*dir;
	struct dirent	*sd;
	int				i;
	int				j;

	i = 0;
	j = 0;
	dir = opendir(".");
	if (dir == NULL)
	{
		printf("error ! Unable to open directory\n");
		return (-1);
	}
	while ((sd = readdir(dir)) != NULL)
	{
		j = 0;
		if (*sd->d_name
			&& (ft_strncmp(sd->d_name, ".", ft_strlen(sd->d_name)) != 0)
			&& (ft_strncmp(sd->d_name, "..", ft_strlen(sd->d_name)) != 0))
		{
			while(sd->d_name[j++])
				i++;
			i++;
		}
	}
	closedir(dir);
	return (i);
}
/*
	function that takes everything in the actual folder and returns it at a char*
	its not in order yet tho
*/
char	*mom_i_am_a_star(char *to_replace)
{
	DIR				*dir;
	struct dirent	*sd;
	int				i;
	char			*rtn;

	i = get_nb_items_chars_in_folder();
	if (i == -1)
		return (NULL);
	rtn = ft_calloc(i + 1, sizeof(char));
	i = 0;
	dir = opendir(".");
	while ((sd = readdir(dir)) != NULL)
	{
		if (*sd->d_name && sd->d_name[0] != '.'
			&& (ft_strncmp(sd->d_name, ".", ft_strlen(sd->d_name)) != 0)
			&& (ft_strncmp(sd->d_name, "..", ft_strlen(sd->d_name)) != 0))
		{
			rtn = ft_strjoin(rtn, " ");
			rtn = ft_strjoin(rtn, sd->d_name);
			i++;
		}
	}
	closedir (dir);
	free (to_replace);
	return (rtn);
}

/*
	function that takes everything in the actual folder and returns it at a char**
*/
char	**mom_i_am_a_star_d(void)
{
	DIR				*dir;
	struct dirent	*sd;
	int				i;
	char			**into_dir;

	i = get_nb_items_in_folder();
	if (i == -1)
		return NULL;
	into_dir = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	dir = opendir(".");
	while ((sd = readdir(dir)) != NULL)
	{
		if (*sd->d_name && sd->d_name[0] != '.'
			&& (ft_strncmp(sd->d_name, ".", ft_strlen(sd->d_name)) != 0)
			&& (ft_strncmp(sd->d_name, "..", ft_strlen(sd->d_name)) != 0))
		{
			into_dir[i] = ft_strdup(sd->d_name);
			i++;
		}
	}
	closedir(dir);
	into_dir = bubble_sort_strarr(into_dir);
	return (into_dir);
}
/*
	function that takes everything in the actual folder and print it out
*/
void	mom_i_am_a_star_p(void)
{
	DIR				*dir;
	struct dirent	*sd;
	int				i;
	char			**into_dir;

	i = get_nb_items_in_folder();
	if (i == -1)
		return ;
	into_dir = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	dir = opendir(".");
	while ((sd = readdir(dir)) != NULL)
	{
		if (*sd->d_name && sd->d_name[0] != '.'
			&& (ft_strncmp(sd->d_name, ".", ft_strlen(sd->d_name)) != 0)
			&& (ft_strncmp(sd->d_name, "..", ft_strlen(sd->d_name)) != 0))
		{
			into_dir[i] = ft_strdup(sd->d_name);
			i++;
		}
	}
	closedir(dir);
	print_out_dir(into_dir);
	free_strrarr(into_dir);
}
