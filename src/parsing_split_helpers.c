#include "../include/minishell.h"

/**
 * @brief First we check if we find << >> or <| or >|
			Then we look if there is quotes or not
			If not we just execute the command
			If yes we check if the index is smaller then the start 
			or the index is bigger then the end
 * 
 * @param s 
 * @param parse_list 
 * @return true 
 * @return false 
 */
bool	check_double_redir(char *s, t_parsing *parse_list)
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
 * @brief First we look if we are a < > or a |
			Then we do the same mechanism as the previous
			function to see if we are within a quote
 * 
 * @param s 
 * @param parse_list 
 * @return true 
 * @return false 
 */

bool	check_in_out_file(char *s, t_parsing *parse_list)
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
 * @brief To create a redirection node
			When there is two symbols
			like >> << 
 * @param s 
 * @param parse_list 
 */
void	init_redir_node_two_char(char *s, t_parsing *parse_list)
{
	parse_list->tkns_list->next
		= node_redir(parse_list->tkns_list->next,
			&s[parse_list->index], 2);
	parse_list->index += 2;
}

/**
 * @brief To create a redirection node
 			When the node is a redir with only one
			symbol
 * 
 * @param s 
 * @param parse_list 
 */
void	init_redir_node_one_char(char *s, t_parsing *parse_list)
{
	parse_list->tkns_list->next
		= node_redir(parse_list->tkns_list->next,
			&s[parse_list->index], 1);
	parse_list->index += 1;
}

/**
 * @brief When the node is a command
 * 
 * @param s 
 * @param parse_list 
 */
void	init_command_node(char *s, t_parsing *parse_list)
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
