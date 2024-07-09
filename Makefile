NAME	=	DunderShell

LIBFT		= ft
LIBFTDIR	= include/libft
MAKELIBFT	= @$(MAKE) -C $(LIBFTDIR)

CFILES	=	environement.c main.c builtin.c execute.c parsing_1.c \
			exit.c export.c env.c unset.c\
			pwd.c echo.c  cd.c\
			str_arr_fcn.c ft_strjoin_free.c  prompt.c  parsing_2.c\
			parsing_utils.c parsing_heredocs_new.c\
			parsing_pipes.c wait_for_pids.c\
			calling_the_execs_shell.c ./look_for.c ./execute_out.c\
			execute_solo.c ft_signals.c logo_n_setup.c parsing_split.c\
			parsing_split2.c parsing_split_helpers.c parsing_3.c\
			parsing_heredocs_new2.c

SRC			= src
INC			= include
OBJ			= obj

HFILES		= colors.h mini_shell.h
OFILES		= $(CFILES:.c=.o)
SRCS		= $(addprefix $(SRC)/, $(CFILES))
OBJS		= $(addprefix $(OBJ)/, $(OFILES))
HEADERS		= $(addprefix $(INC)/, $(HFILES))

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g 
RM		=	rm -rf

$(OBJ)/%.o:	$(SRC)/%.c
			$(CC) $(CFLAGS) -I$(LIBFTDIR) -I$(INC) -I. -c $< -o $@
			
$(NAME)	:	$(OBJ) $(OBJS)
			$(MAKELIBFT) bonus
			$(CC) $(OBJS) -L$(LIBFTDIR) -lft -Llinlib -lreadline -lcurses -o $(NAME) 

$(OBJ):
			@mkdir -p $(OBJ)

all		:	$(NAME)

clean	:
			$(MAKELIBFT) fclean
			@$(RM) $(OBJS)

fclean	:	clean
			@$(RM) $(NAME) $(OBJ)
			
re		:	fclean all

run :		fclean all 
			$(RUN)

.PHONY	:	all clean fclean re 

.SILENT :   clean fclean

