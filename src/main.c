/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 10:06:15 by pirichar          #+#    #+#             */
/*   Updated: 2022/06/04 09:41:27 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "../include/minishell.h"

// void	print_env()
// {
// 	char	*tmp;


// }

// int main(int argc, char **argv, char **env)
// {
// 	(void)argc;
// 	(void)argv;
// 	char *line;
// 	int		i;
// 	char **path;	
// 	path = path_to_strarr(env);
// 	i = 0;
// 	while(1)
// 	{
// 		line = readline("MINISHELL: ");
// 		if (line && *line) // not sure I need this but saw it in the man
// 			add_history(line);
// 		while(path[i])
// 		{
// 			if (search_path(path[i], line) == true)
// 				printf("VALID COMMAND WILL HANDLE LATER\n");
// 			else
// 				printf("Invalid command\n");
// 			i++;
// 		}
// 		if (ft_strncmp(line, "env",5) == 0)
// 		{
// 			i = 0;
// 			while(env[i])
// 			{
// 				printf("%s\n",env[i]);
// 				i++;
// 			}
// 			printf("\n");
// 			free(line);
// 		}
// 		else if(ft_strncmp(line, "exit",5) == 0)
// 		{
// 			free(line);
// 			return (0);
// 		}
// 		else
// 			free(line);
// 	}
// 	free(path);
// }


int	nb_of_paths(char **path)
{
	int i;

	i = 0;
	while(path[i])
		i++;
	return (i);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char *line;
	int		i;
	char **path;
	
	path = path_to_strarr(env);
	while(1)
	{
		i = 0;
		line = readline("MINISHELL: ");
		if (line && *line) // not sure I need this but saw it in the man
			add_history(line);
		/* parse the line here
			1- first round check the special characters - set the quotes to their number ;
				check for the start at the same time and filter the " " ' ' and spaces at first
				check the number of pipe 
				check the ammount of strings to malloc
				at the end if quotes % 2 != 0 invalid command
				
			2- reparse taking in count special character and fill the cmd array spliting with spaces
				-- FOR THE CMDS ; I WILL NEED TO IMPLEMENT A LIST OR A STRUCT WITH THE STRING ITSELF AND ITS POSITION + A POINTER TO THE NEXT ELEMENT --
				--ASSUME THAT IF YOU ARE IN QUOTES YOULL BE IN AN OTHER MODE OF PARSING--
				--PARSE EVERYTHING THEN RUN ALL IN PARRALLEL LIKE YOU DID IN PIPEX--
				***** << allo " ; IN THIS SCENARIO THE " QUOTE WOULD PROMPT THE QUOTE PROMPT BEFORE THE HERE DOC SO THE PROMPT GOES OVER ALL ****
				If you encounter a < dup2 the input with the file; open as well; if you dont find the file return and empty pipe and prompt an error
				if you encounter a << at the begining of the line with  a valid herdoc word after you prompt an heredoc and pass the output to the other command if there is any
				if you encounter a > you dup2 the ouput and open the file ** THINK ABOUT THIS ONE COMPARE TO YOUR PIPEX
				if you encounter a >> you dup2 the ouput and open the file with append
				if you encounter a " " any character goes into the array no mather what except for valid path with $; each time you hit a " nb_dbquote-- ; dbquotes = true;enter dbquotes mode
				if you encounter a ' ' any character goes into the array untill you hit another one each time you hit a ' nb_quote-- ; quotes = true;enter quote mode
				if you encounter a $	if the word next to the $ is a valid env var the env var pointed by the word replace the word into the array
				if you encounter a space you should try to access the word and see if its a valid command
					if its not valid prompt a message error and pass an empty pipe to next command 
						if last command just prompt empty message and return prompt
					if its valid add everything to the string formed by the accessed command so you can use them as its arguments ; nb of wd in this node ++;
					each time you cross a space nb of word in this node ++
					go untill you meet the \0 or a |  character or a < or a > or a & 
				if you encounter a | 	you must absolutely stop the actual array with \0  and move to the next command; pipe--
					you could also check after a space how many space there is before to add the next argument the the array
					while it is space and the next character is a space or the same kind of quote you might be in i++;
					if char +1 = \0 stop the parsing of the line
				if you encounter a \0  stop the parsing of the line
				else
					you add the char into the array 
			3- give that to the command that search the path OR exec the cmds
							*/
		/* 
			initiate program for this and work in the child after
			create an array of pids depending on the count of commands
			pass the array of argument as it was char **argv in calling_the_execs
			Calculate the amount of argument and pass it as argc 
			set fd in ; set fd out; prepare stuff for the execute command function
		*/
		while(path[i]) //this could be inserted into something else I used it to see if the command is in the path or not
		{
			if (search_path(path[i], line) == true)
				break ;
			i++;
		}
		if (i == nb_of_paths(path))
				printf("Invalid command\n");
		else
		{
			printf("VALID COMMAND WILL HANDLE LATER\n");
			//here I should probably fork and start to do stuff with that command
		}

		if (ft_strncmp(line, "env",5) == 0)
		{
			i = 0;
			while(env[i])
			{
				printf("%s\n",env[i]);
				i++;
			}
			printf("\n");
			free(line);
		}
		else if(ft_strncmp(line, "exit",5) == 0)
		{
			free(line);
			return (0);
		}
		else
			free(line);
	}
	free(path);
}