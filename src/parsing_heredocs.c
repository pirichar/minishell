#include "../include/minishell.h"
#include <stdio.h>


/*
	Probablement qu'il faudrait que l'on change la manière dont on call les redirection pour les mettre avec leur bon pipe
	Ca serait plus simple pour reproduire le comportement de bash qui ne passe pas l'input entre les pipes mais bien l'output du pipe
	à l'input de la prochaine commande. 
	Autrement dit, il ne faudrait pas que si on redirige l'entrée dans la première commande, que ce soit passée vers la 2e pareil pour l'output ;
	Peut-être que cela pourrait être corrigée directement dans le child ou dans l'exécution, oui mais ca va prendre une redirection par tkns_list

	Sinon on pourrait mettre le parse->infile dans la token list et prendre ça pour l'exécution
	Il faudrait à chaque fois qu'on tape un | faire avancer la liste pour être certain d'être au bon endroit

	quand on fait > PL dans bash ça créer un fichier PL
	quand on fait  > PL | echo allo ça créer un fichier echo allo dans bash
	*****Si on veut garder notre programme comme ça il faudrait que la ligne d'en haut soit vrai et qu'on fasse une exception pour le cas ou on a > FILE | 
	
	Ca veut donc dire que bash ne passe pas les redirections d'output entre les pipes ?
	Par contre ça serait surement plus simple de faire une règle que si ya juste une redirection sans commande (d'entrée du moins) on la passe pas
	> PL echo allo | echo popa  il faudrait régler ce cas et pour faire cela il faudrait que chacune des redirections soit traitée
	dans sa propre liste en fonction de ou elle est dans le LINE 

	dans BASH > PL echo allo | echo popa 	ca ca écris dans PL et echo popa dans le term
	dans BASH > PL | echo allo 				
	dans BASH < PL | > PLO 					ca ouvre PLO mais ca ecris rien dedans
	dans BASH < PL 							ca fait rien
	dans BASH < PL | cat 					ca fait rien

	dans ZSH > PL echo allo | echo popa 	ca echo popa dans le terme mais n'écris pas allo dans PL;
	dans ZSH > PL | echo allo 				ca créer un fichier echo allo et ça attend le STDIN est ouvert jusqu'à ce que l'on fasse CTRL C
	dans ZSH < PL | > PLO 					ca ouvre PLO et ca ecris dedans
	dans ZSH < PL 							ca affiche ce qu'il y a dans PL dans le stdin avec un end
	dans ZSL < PL | cat 					ca affiche PL car < PL affiche de base dans le stdout

	dans DUNDER < PL | cat 					ca marche mais pas pour la bonne raison, ca marche pcq on passe le stdin pas pcq on l'imprime dans le term
	dans DUNDER < PL | > PLO 				ca ouvre PLO mais ca ecris rien dedans
	Dans DUNDER < PL						ca fait rien
	dans DUNDER echo allo > PL				Régler ca marche j'ai ajouté look_for_echo dans execute solo pour eviter que ca se fasse ds le child
	dans DUNDER > PL echo allo | echo popa 	ca ecris les deux dans PL **** PROBLEME *****
	dans DUNDER > PL | echo allo 			ca segfault XD 				*** PROBLEME VOIR NOTION DANS TO-DO POUR DÉTAILS****; 


*/
int	check_metachar(t_parsing *parse_list)
{
	int	j;

	j = 0;
	while (parse_list->tkns_list != NULL)
	{
		while (parse_list->tkns_list != NULL && parse_list->tkns_list->data[j])
		{
			if (ft_strchr("<|>", parse_list->tkns_list->data[0])) //change for something like:  if (parse_list->tkns_array->type == "APPEND") then do each type or tok_type != CMD (donc doit etre redir)
			{
				if (parse_list->tkns_list->data[0] == '<')
				{
					if (parse_list->tkns_list->tok_type == TRUNC)
					{
						if (check_file_and_delim_name(parse_list->tkns_list, j + 1) == 1)
							return (1);
						printf("do the heredoc\n");
						parse_list->file = open("./div/here_doc", O_CREAT | O_WRONLY | O_APPEND, 0777);
						if (parse_list->file == -1)
							return (1);//should call the exit function here
						while (1)
						{
							write(1, "heredoc>", 9);
							parse_list->buf = get_next_line(0);
							if (!ft_strncmp(parse_list->tkns_list->next->data, parse_list->buf, ft_strlen(parse_list->tkns_list->next->data)))
								break ;
							write(parse_list->file, parse_list->buf, ft_strlen(parse_list->buf));
							free (parse_list->buf);
						}
						free (parse_list->buf);
						close(parse_list->file);
						parse_list->infile = open("./div/here_doc", O_RDONLY);
						j++;
						break ;
					}
					if (parse_list->tkns_list->data[1] == '>')
					{
						if (check_file_and_delim_name(parse_list->tkns_list, j + 1) == 1)
							return (1);
						printf("do the redir out\n");
						break ;
					}
					if (check_file_and_delim_name(parse_list->tkns_list, j) == 1)
						return (1);
					parse_list->infile = open(parse_list->tkns_list->next->data, O_RDONLY);
					if (parse_list->infile == -1)
						fprintf(stderr, "Could not open input file\n");
					else
						printf("did the redir in this is parse_list->infile %d\n", parse_list->infile);
				}
				if (parse_list->tkns_list->data[0] == '>')
				{
					if (parse_list->tkns_list->data[1] == '>')
					{
						if (check_file_and_delim_name(parse_list->tkns_list, j + 1) == 1)
							return (1);
						parse_list->outfile = open(parse_list->tkns_list->next->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
						if (parse_list->outfile == -1)
						{
							fprintf(stderr, "MINISHELL: Could not open output file\n");
							return (1);
						}
						printf("did_the_append_out\n");
						j++;
						break ;
					}
					if (parse_list->tkns_list->data[1] == '|' || parse_list->tkns_list->data[1] == '\0')
					{
						if (check_file_and_delim_name(parse_list->tkns_list, j + 1) == 1)
							return (1);
						parse_list->outfile = open(parse_list->tkns_list->next->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
						if (parse_list->outfile == -1)
						{
							fprintf(stderr, "MINISHELL: Could not open output file\n");
							return (1);
						}
						printf("did the redir out\n");
						break ;
					}
				}
				if (parse_list->tkns_list->tok_type == PIPE)
				{
					if (check_pipe_name(parse_list->tkns_list, j) == 1)
						return (1);
					// printf("do the pipe\n");
					break ;
				}
				if (parse_list->tkns_list->data[1] != '\0')
				{
					printf("Dundershell: syntax error near unexpected token `%c'\n", parse_list->tkns_list->data[1]);
					return (1);
				}
			}
			j++;
		}
		j = 0;
		parse_list->tkns_list = parse_list->tkns_list->next;
	}
	return (0);
}


//quite sure this is not useful. I made my own "make tokens node" functions

// void	prep_next_node(t_parsing *parse_list, int ind_vector, int ind_array)
// {
// 	parse_list->tkns_list->next = calloc(sizeof(t_tkns), 1);
// 	parse_list->tkns_list->next->prev = parse_list->tkns_list; //next->prev????
// 	parse_list->tkns_list->next->start = parse_list->tkns_list->start;
// 	parse_list->tkns_list->vector_cmd[ind_vector] = NULL;
// 	parse_list->tkns_list = parse_list->tkns_list->next;
// 	parse_list->tkns_list->vector_cmd = calloc(sizeof(char **),
// 			(count_cmd(parse_list->tkns_array, ind_array + 1) + 1));
// 	parse_list->tkns_list->argv_pos = parse_list->tkns_list->prev->argv_pos + 1;
// 	parse_list->tkns_list->vector_cmd[0]
// 		= calloc(ft_strlen(parse_list->tkns_array[++ind_array])
// 			+ 1, sizeof(char));
// 	parse_list->nb_of_pipes++;
// 	parse_list->i_vect = 0;
// 	parse_list->i_arr++;
// 	parse_list->i_str = 0;
// }

void	alloc_vector(t_parsing *parse_list, int ind_vector,
	int ind_array, bool to_free)
{
	if (to_free == true)
		free(parse_list->tkns_list->vector_cmd[ind_vector]);
	parse_list->tkns_list->vector_cmd[ind_vector]
		= calloc(ft_strlen(parse_list->tkns_list->vector_cmd[ind_array]) //to confirm size here, im unsure
			+ 1, sizeof(char));
}

/*
	// DEBUG - HERE i added if parse_list ; we had a segfault 
// */
// int	is_it_redir(t_parsing *parse_list)
// {
// 	if (parse_list && ft_strchr("<>", parse_list->tkns_array[parse_list->i_arr][parse_list->i_str]))
// 	{
// 		parse_list->i_arr += 2;
// 		if (parse_list->tkns_array[parse_list->i_arr - 1] == NULL
// 			|| parse_list->tkns_array[parse_list->i_arr] == NULL)
// 		{
// 			parse_list->tkns_list->vector_cmd[parse_list->i_vect] = NULL;
// 			return (1);
// 		}
// 		alloc_vector(parse_list, parse_list->i_vect, parse_list->i_arr, true);
// 		return (0);
// 	}
// 	return (2);
// }

// int	is_it_pipe(t_parsing *parse_list)
// {
// 	if (parse_list->tkns_array[parse_list->i_arr] && ft_strchr("|", parse_list->tkns_array[parse_list->i_arr]
// 			[parse_list->i_str]))
// 	{
// 		if (parse_list->i_vect == 0
// 			&& parse_list->tkns_list->vector_cmd[parse_list->i_vect][0] == '\0')
// 		{
// 			parse_list->i_arr++;
// 			alloc_vector(parse_list, parse_list->i_vect,
// 				parse_list->i_arr, true);
// 			return (0);
// 		}
// 		prep_next_node(parse_list, parse_list->i_vect, parse_list->i_arr);
// 		return (0);
// 	}
// 	return (1);
// }
