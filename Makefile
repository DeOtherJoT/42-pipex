#EXEC#

NAME	= pipex

#COMMANDS & FLAGS#

GCC		= gcc -Wall -Wextra -Werror
RM		= rm -rf

#PATH#

INC		= -Iincludes
SRC_DIR	= sources/
GNL_DIR	= $(SRC_DIR)gnl/
MAN_DIR	= $(SRC_DIR)mandatory/
BNS_DIR	= $(SRC_DIR)bonus/

MAIN	= $(SRC_DIR)main.c

#SOURCE FILES#

MAN_SRC	=	$(addprefix $(MAN_DIR), init_struct.c utils.c utils2.c pipex.c)
BNS_SRC	=	$(addprefix $(GNL_DIR), get_next_line.c get_next_line_utils.c) \
			$(addprefix $(MAN_DIR), utils.c utils2.c) \
			$(addprefix $(BNS_DIR), pipex_bonus.c utils_bonus.c utils2_bonus.c)
MAN_OBJ	=	$(MAN_SRC:.c=.o)
BNS_OBJ	=	$(BNS_SRC:.c=.o)

#RECIPES#

all		: $(NAME)

%.o		: %.c
	$(GCC) $(INC) -c $< -o $@

$(NAME)	: $(MAN_OBJ)
	$(GCC) $(INC) -o $(NAME) $(MAIN) $(MAN_OBJ)

bonus	: $(BNS_OBJ)
	$(GCC) $(INC) -o $(NAME) $(MAIN) $(BNS_OBJ)

clean	:
	$(RM) $(MAN_OBJ) $(BNS_OBJ)

fclean : clean
	$(RM) $(NAME)

re		: fclean all

re_bns	: fclean bonus

.PHONY	: all bonus clean fclean re re_bns