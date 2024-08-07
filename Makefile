NAME	=	minishell

LIBFT		= ft
LIBFTDIR	= include/libft
MAKELIBFT	= @$(MAKE) -C $(LIBFTDIR)
OS        = $(shell uname)
ARCH    = $(shell uname -m)

ifeq ($(OS), Linux)
LIB_RDLINE    = linlib
else ifeq ($(OS), Darwin)
    ifeq ($(ARCH), x86_64)
    LIB_RDLINE    = lib
    else
    LIB_RDLINE    = m1lib
    endif
else
$(error "unsupported OS")
endif

CFILES	=	environement.c main.c builtin.c execute.c parsing_1.c \
			exit.c export.c env.c unset.c\
			pwd.c echo.c  cd.c\
			str_arr_fcn.c ft_strjoin_free.c  prompt.c  parsing_2.c\
			parsing_utils.c parsing_heredocs_new.c\
			wait_for_pids.c\
			calling_the_execs_shell.c look_for.c execute_out.c\
			execute_solo.c ft_signals.c logo_n_setup.c parsing_split.c\
			parsing_split2.c parsing_split_helpers.c parsing_3.c\
			parsing_heredocs_new2.c arena.c arena_str.c parsing_expand.c\
			parsing_heredocs_utils.c parsing_utils2.c cleanup.c export_split.c\

SRC			= src
INC			= include
OBJ			= obj

HFILES		= colors.h mini_shell.h arena.h
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
			$(CC) $(OBJS) -L$(LIBFTDIR) -lft -L$(LIB_RDLINE) -lreadline -lcurses -o $(NAME) 

$(OBJ):
			@mkdir -p $(OBJ)

all		:	$(NAME)

clean	:
			$(RM) $(OBJS)
			$(MAKELIBFT) fclean

fclean	:	clean
			$(RM) $(NAME) $(OBJ)
			
re		:	fclean all

run :		fclean all 
			$(RUN)

.PHONY	:	all clean fclean re 

.SILENT :   clean fclean

