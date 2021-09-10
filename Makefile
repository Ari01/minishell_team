# VAR

NAME			= minishell
LIBFT 			= libft/libft.a

SRCS			= main.c \
parsing.c \
builtin.c \
pipe.c \
error.c \
cmd.c \
redirection.c \
utils.c

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
				$(MAKE) bonus -C libft

.c.o :
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean :
				$(MAKE) clean -C libft
				$(RM) $(OBJS)

fclean :		clean
				$(MAKE) fclean -C libft
				$(RM) $(NAME)
				$(RM) .*.swp

re :			clean fclean all

.PHONY :		all clean fclean re
