#include "../include/minishell.h"

/**
 * @brief 
 * // TODO Trouver un bon nom pour la fonction
 * @param s 
 * @param parse_list 
 * @return true 
 * @return false 
 */
bool	should_do_it(char *s, t_parsing *parse_list)
{
	return (((s[parse_list->index] == '<'
				|| s[parse_list->index] == '>')
			&& (s[parse_list->index + 1] == '<'
				|| s[parse_list->index + 1] == '>'
				|| s[parse_list->index + 1] == '|'))
		&& ((parse_list->quotes == false)
			|| (parse_list->quotes == true
				&& (parse_list->index < parse_list->quote_start
					|| parse_list->index > parse_list->quote_end))));
}

/**
 * @brief 
 * // TODO Trouver un nom pour la fonction
 * @param s 
 * @param parse_list 
 * @return true 
 * @return false 
 */

bool	should_do_it_else(char *s, t_parsing *parse_list)
{
	return ((s[parse_list->index] == '<'
			|| s[parse_list->index] == '>'
			|| s[parse_list->index] == '|')
		&& ((parse_list->quotes == false)
			|| (parse_list->quotes == true
				&& (parse_list->index < parse_list->quote_start
					|| parse_list->index > parse_list->quote_end))));
}
/**
 * @brief 
 * // TODO trouver un nom intelligent
 * @param s 
 * @param parse_list 
 */
void	helper1(char *s, t_parsing *parse_list)
{
	parse_list->tkns_list->next
		= node_redir(parse_list->tkns_list->next,
			&s[parse_list->index], 2);
	parse_list->index += 2;
}

/**
 * @brief 
 * // TODO trouver un nom intelligent
 * @param s 
 * @param parse_list 
 */
void	helper2(char *s, t_parsing *parse_list)
{
	parse_list->tkns_list->next
		= node_redir(parse_list->tkns_list->next,
			&s[parse_list->index], 1);
	parse_list->index += 1;
}

/**
 * @brief 
 * // TODO trouver un nom intelligent
 * @param s 
 * @param parse_list 
 */
void	helper3(char *s, t_parsing *parse_list)
{
	parse_list->tkns_list->next
		= make_node(parse_list->tkns_list->next,
			&s[parse_list->index]);
	while (s[parse_list->index]
		&& ft_isspace(s[parse_list->index]) == false)
		parse_list->index += 1;
	if (parse_list->tkns_list->tok_type == CMD)
		parse_list->cmd_count++;
}
