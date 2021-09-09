# VAR

NAME			= minishell
LIBFT 			= libft/libft.a

SRCS			= main.c \
parsing.c \
builtin.c

OBJS			= $(SRCS:.c=.o)

CC				= clang
CFLAGS			= -Wall -Wextra -Werror
LFLAGS			= -L libft -lft -lreadline
RM				= rm -f

# RULES 

all :			$(NAME)

$(NAME) :		$(OBJS) $(LIBFT)
				$(CC) $(CFLAGS) $(OBJS) -o $@ $(LFLAGS)

$(LIBFT) :		
				cd libft && $(MAKE) $(BONUS)

.c.o :
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean :
				$(RM) $(OBJS)

fclean :		clean
				$(RM) $(NAME)

re :			clean fclean all

.PHONY :		all clean fclean re
