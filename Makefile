# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/09 19:48:16 by xuwang            #+#    #+#              #
#    Updated: 2021/09/30 18:25:31 by dchheang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# VAR

NAME			= minishell
LIBFT 			= libft/libft.a
INC				= -I.

SRCS			= main.c \
				  lexer_parser/lexer.c \
				  lexer_parser/grammar.c \
				  lexer_parser/parsing.c \
				  lexer_parser/get_stream.c \
				  lexer_parser/get_stream_utils.c \
				  execution/pipe.c \
				  execution/cmd.c \
				  execution/redirection.c \
				  execution/exec.c \
				  execution/stream.c \
				  execution/var.c \
				  utils/error.c \
				  utils/utils.c \
				  utils/print.c \
				  builtin/builtin.c \
				  builtin/echo.c \
				  builtin/cd.c \
				  builtin/pwd.c \
				  builtin/exit.c \
				  builtin/env.c \
				  builtin/export.c \
				  builtin/unset.c \
				  builtin/utils.c \
				  history/history.c 

OBJS			= $(SRCS:.c=.o)

CC				= clang
CFLAGS			= -Wall -Wextra -Werror
LFLAGS			= -L libft -lft -lreadline
RM				= rm -f

# RULES 

all :			$(NAME)

$(NAME) :		$(OBJS) $(LIBFT)
				$(CC) $(CFLAGS) $(INC) $(OBJS) -o $@ $(LFLAGS)

debug :			$(OBJS) $(LIBFT)
				$(CC) $(CFLAGS) -g3 -fsanitize=address $(INC) $(OBJS) -o $@ $(LFLAGS)

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
				$(RM) .*.swp
				$(RM) */.*.swp

re :			clean fclean all

.PHONY :		all clean fclean re
