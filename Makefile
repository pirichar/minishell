SRCS	=	src/environement.c src/main.c src/builtin.c src/execute.c src/parsing_1.c \
			src/exit.c src/export.c src/env.c src/unset.c\
			src/pwd.c src/echo.c  src/cd.c\
			src/str_arr_fcn.c src/ft_strjoin_free.c  src/prompt.c  src/parsing_2.c \
			src/parsing_utils.c src/parsing_heredocs.c src/parsing_redir_in.c \
			src/parsing_redir_out.c src/parsing_pipes.c src/wait_for_pids.c\
			src/calling_the_execs_shell.c ./src/look_for.c ./src/execute_out.c\
			src/execute_solo.c src/ft_signals.c src/logo_n_setup.c

HEADERS	=	minishell.h colors.h

vpath %.h include/

OB		= @mkdir -p objs && mv ./src/*.o ./objs/ 

OBJS	=	${SRCS:.c=.o}

CC		=	@gcc

RM		=	@rm -rf

INC 	= include

CFLAGS	=	-Wall -Wextra -Werror -o DunderShell -g  -I${INC}

LIBS	=	include/Libft/libft/libft.a -lreadline 

NAME	=	DunderShell

FTMAKE	=	@cd include/Libft/libft && make -s 

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
			$(CC) $(SRCS) $(LIBS) -Lm1lib -lhistory -lcurses $(CFLAGS)
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
			
WSL		:	$(SRCS) $(OBJS) $(HEADERS)
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

