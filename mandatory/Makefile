#EXEC#

NAME	= pipex

#COMMANDS & FLAGS#

GCC		= gcc -Wall -Wextra -Werror
RM		= rm -rf

#PATH#

INC		= -Iincludes
SRC_DIR	= srcs/
MAIN	= main.c

#SOURCE FILES#

SRCS	=	$(addprefix $(SRC_DIR), init_struct.c pipex.c utils.c utils2.c)
OBJS	=	$(SRCS:.c=.o)

#RECIPES#

all		: $(NAME)

$(NAME)	: $(OBJS)
	$(GCC) $(INC) -o $(NAME) $(MAIN) $(OBJS)

%.o		: %.c
	$(GCC) $(INC) -c $< -o $@

clean	:
	$(RM) $(OBJS)

fclean	: clean
	$(RM) $(NAME)

re		: fclean all

.PHONY	: all clean fclean