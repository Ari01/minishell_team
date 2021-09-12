# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/09 19:48:16 by xuwang            #+#    #+#              #
#    Updated: 2021/09/12 17:58:19 by xuwang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# VAR
NAME			= minishell
LIBFT 			= libft/libft.a
INC				= -I.

SRCS			= main.c \
				parsing.c \
				builtin/echo.c \
				builtin/cd.c \
				builtin/pwd.c \
				builtin/exit.c \
				builtin/env.c \
				builtin/export.c \
				builtin/unset.c \
				builtin/utils.c 


OBJS			= $(SRCS:.c=.o)

CC				= clang
CFLAGS			= -Wall -Wextra -Werror
LFLAGS			= -L libft -lft -lreadline
RM				= rm -f

# RULES 

all :			$(NAME)

$(NAME) :		$(OBJS) $(LIBFT)
				$(CC) $(CFLAGS) $(INC) $(OBJS) -o $@ $(LFLAGS)

$(LIBFT) :		
				$(MAKE) bonus -C libft

.c.o :
				$(CC) $(CFLAGS) $(INC) -c $< -o $(<:.c=.o)

clean :
				$(MAKE) clean -C libft
				$(RM) $(OBJS)

fclean :		clean
				$(MAKE) fclean -C libft
				$(RM) $(NAME)

re :			clean fclean all

.PHONY :		all clean fclean re
