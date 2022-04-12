SRCS		= init_struct.c utils.c utils2.c pipex.c
OBJS		= $(SRCS:.c=.o)
B_SRCS		= get_next_line.c get_next_line_utils.c pipex_bonus.c utils.c \
			  utils2.c utils2_bonus.c utils_bonus.c
B_OBJS		= $(B_SRCS:.c=.o)
GCC_T		= gcc -Wall -Werror -Wextra -g -fsanitize=address
GCC			= gcc -Wall -Werror -Wextra
NAME		= pipex
ARNAME		= pipex.a
B_ARNAME	= pipex_b.a
ARRCS		= ar rcs
RM			= rm -f

all : $(NAME)

%.o : %.c
	$(GCC) -I . -c $< -o $@ -D BUFFER_SIZE=10

$(NAME) : $(OBJS)
	$(ARRCS) $(ARNAME) $(OBJS)
	$(GCC) $(ARNAME) main.c -o $(NAME)

bonus : $(B_OBJS)
	$(ARRCS) $(B_ARNAME) $(B_OBJS)
	$(GCC) $(B_ARNAME) main.c -o $(NAME)

clean :
	$(RM) $(OBJS) $(B_OBJS) $(ARNAME) $(B_ARNAME)

fclean : clean
	$(RM) $(NAME) *.txt

re : fclean all

.PHONY : all clean fclean re
