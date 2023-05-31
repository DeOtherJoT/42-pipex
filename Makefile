#EXEC#

NAME	= pipex

#COMMANDS & FLAGS#

GCC		= gcc -Wall -Wextra -Werror
RM		= rm -rf
FSAN	= -fsanitize=address -g3

#PATH#

INC		= -Iincludes
SRC_DIR	= sources/
GNL_DIR	= $(SRC_DIR)gnl/
MAN_DIR	= $(SRC_DIR)mandatory/
BNS_DIR	= $(SRC_DIR)bonus/
BN2_DIR	= $(SRC_DIR)new_bonus/

MAIN	= $(SRC_DIR)main.c

#SOURCE FILES#

MAN_SRC	=	$(addprefix $(MAN_DIR), init_struct.c utils.c utils2.c pipex.c)
BNS_SRC	=	$(addprefix $(GNL_DIR), get_next_line.c get_next_line_utils.c) \
			$(addprefix $(MAN_DIR), utils.c utils2.c) \
			$(addprefix $(BNS_DIR), pipex_bonus.c utils_bonus.c utils2_bonus.c)
BN2_SRC	=	$(addprefix $(GNL_DIR), get_next_line.c get_next_line_utils.c) \
			$(addprefix $(MAN_DIR), utils.c utils2.c) \
			$(addprefix $(BN2_DIR), exec2.c pipex2.c utils_b2.c) 
MAN_OBJ	=	$(MAN_SRC:.c=.o)
BNS_OBJ	=	$(BNS_SRC:.c=.o)
BN2_OBJ	=	$(BN2_SRC:.c=.o)

#RECIPES#

all		: $(NAME)

%.o		: %.c
	$(GCC) $(INC) -c $< -o $@

$(NAME)	: $(MAN_OBJ)
	$(GCC) $(INC) -o $(NAME) $(MAIN) $(MAN_OBJ)

bonus	: $(BNS_OBJ)
	$(GCC) $(INC) -o $(NAME) $(MAIN) $(BNS_OBJ)

bonus2	: $(BN2_OBJ)
	$(GCC) $(INC) -o $(NAME) $(MAIN) $(BN2_OBJ)

clean	:
	$(RM) $(MAN_OBJ) $(BNS_OBJ) $(BN2_OBJ)

fclean : clean
	$(RM) $(NAME)

re		: fclean all

re_bns	: fclean bonus

re_bn2	: fclean bonus2

.PHONY	: all bonus bonus2 clean fclean re re_bns re_bn2 