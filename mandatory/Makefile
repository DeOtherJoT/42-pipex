SRCS	= init_struct.c utils.c utils2.c pipex.c
OBJS	= $(SRCS:.c=.o)
GCC_T	= gcc -Wall -Werror -Wextra -g -fsanitize=address
GCC		= gcc -Wall -Werror -Wextra
NAME	= pipex
ARNAME	= pipex.a
ARRCS	= ar rcs
RM		= rm -f

all : $(NAME)

.c.o :
	$(GCC) -I . -c $< -o $(<:.c=.o)

$(NAME) : $(OBJS)
	$(ARRCS) $(ARNAME) $(OBJS)
	$(GCC) $(ARNAME) main.c -o $(NAME)

clean :
	$(RM) $(OBJS) $(ARNAME)

fclean : clean
	$(RM) $(NAME) *.txt

re : fclean all

.PHONY : all clean fclean re
