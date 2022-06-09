# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/24 11:00:19 by jvigneau          #+#    #+#              #
#    Updated: 2022/06/09 15:38:36 by jvigneau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

define JR
	BIG LEAK!!!! A PICTURE OF ME WORKING

                        .="=.
                      _/.-.-.\_     _
                     ( ( o o ) )    ))
                      |/  "  \|    //
      .-------.        \'---'/    //
     _|~~ ~~  |_       /`"""`\\  ((
   =(_|_______|_)=    / /_,_\ \\  \\
     |:::::::::|      \_\\_'__/ \  ))
     |:::::::[]|       /`  /`~\  |//
     |o=======.|      /   /    \ //
     `"""""""""`  ,--`,--'\/\   //
                  '-- "--'  '--'
endef
export JR

define TEA

		TEABAG THAT MOTHERF***ER

            .------.____
         .-'       \ ___)
      .-'         \\\\
   .-'        ___  \\)
.-'          /  (\  |)
         __  \  ( | |
        /  \  \__'| |
       /    \____).-'
     .'       /   |
    /     .  /    |
  .'     / \/     |
 /      /   \     |
       /    /    _|_
       \   /    /\ /\\
        \ /    /__v__\\
         '    |       |
              |     .#|
              |#.  .##|
              |#######|
              |#######|

endef
export TEA

SRCS	=	src/environement.c src/main.c src/builtin.c src/pipex.c src/parsing_1.c

HEADERS	=	minishell.h colors.h

vpath %.h include/

OB		= @mkdir -p objs && mv ./src/*.o ./objs/ 

OBJS	=	${SRCS:.c=.o}

CC		=	@gcc

RM		=	@rm -rf

CFLAGS	=	-Wall -Wextra -Werror -o DunderShell

LIBS	=	include/Libft/libft/libft.a -lreadline

NAME	=	DunderShell

FTMAKE	=	@cd include/Libft/libft && make -s 

RUN		=	./DunderShell

CLS		= 	clear

all		:	$(NAME)
			

$(NAME)	:	$(SRCS) $(OBJS) $(HEADERS)
			@if [ ! -d "./objs" ]; then \
				clear && \
				echo "__________________________________" && \
				echo "\n       Compiling.....\n" && \
				echo "__________________________________" && \
				touch a ;\
			fi 
			$(FTMAKE) 
			@ if [ ! -d "./objs" ]; then \
				echo "__________________________________" && \
				echo "\n      Libft compiled \n" && \
				echo "__________________________________"; \
			fi
			$(CC) $(SRCS) $(LIBS) $(CFLAGS)
			@if [ -p "./objs" ]; then \
				rm -rf ./objs; \
			fi
			$(OB)
			@if [ -f "./a" ]; then \
				sleep 1 && \
				echo "__________________________________" && \
				echo "\n Project succesfully compiled!\n" && \
				echo "__________________________________" && \
				rm -f ./a; else \
				clear && \
				echo "__________________________________" && \
				echo "\n\n             Done\n" && \
				echo "__________________________________"; \
			fi
			
clean	:	
			@clear
			@echo "__________________________________"
			@echo "\n     Clearing object files... \n"
			@echo "__________________________________"
			${RM} ./objs
			$(FTMAKE) $@
			@sleep 1
			@echo "__________________________________"
			@echo "\n     Cleaning Successful! \n"
			@echo "__________________________________"
			@sleep 1

fclean	:	clean
			@echo "__________________________________"
			@echo "\n     Clearing other files... \n"
			@echo "__________________________________"
			@if [ -f "./DunderShell" ]; then \
				rm -rf ./DunderShell; \
			fi
			$(FTMAKE) $@
			@sleep 1
			@echo "__________________________________"
			@echo "\n         Cleaning done!\n"
			@echo "__________________________________"
			@sleep 1
			
re		:	fclean all

run :		fclean all 
			$(RUN)

jr		: 
			clear
			@echo "$$JR"

tea	:
			clear
			@echo "$$TEA"

.PHONY	:	all clean fclean re bonus jr

.SILENT :   clean fclean

