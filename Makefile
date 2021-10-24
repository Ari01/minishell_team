# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/09 19:48:16 by xuwang            #+#    #+#              #
#    Updated: 2021/10/24 13:38:44 by dchheang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# VAR

NAME			= minishell
LIBFTDIR		= includes/libft
LIBFT 			= $(LIBFTDIR)/libft.a
INC				= -I includes

SRCS			= src/main/main.c \
				src/main/minishell.c \
				src/utils/memory.c \
				src/utils/memory2.c \
				src/lexer_parser/lexer.c \
				src/lexer_parser/grammar.c \
				src/lexer_parser/parsing.c \
				src/lexer_parser/get_stream.c \
				src/lexer_parser/get_stream_utils.c \
				src/lexer_parser/ft_trim.c \
				src/execution/pipe.c \
				src/execution/cmd.c \
				src/execution/redirection.c \
				src/execution/read_input.c \
				src/execution/read_error.c \
				src/execution/exec.c \
				src/execution/var.c \
				src/execution/utils.c \
				src/utils/error.c \
				src/utils/utils.c \
				src/utils/print.c \
				src/builtin/builtin.c \
				src/builtin/echo.c \
				src/builtin/cd.c \
				src/builtin/pwd.c \
				src/builtin/exit.c \
				src/builtin/env.c \
				src/builtin/export.c \
				src/builtin/export_utils.c\
				src/builtin/unset.c \
				src/builtin/utils.c \
				src/history/history.c \
				src/signal/signal.c \
				src/parsing/handling_quot1.c \
				src/parsing/handling_quot2.c \
				src/parsing/handling_quot3.c \
				src/parsing/handling_flag.c\
				src/parsing/parsing_utils.c \
				src/parsing/handling_dollar1.c\
				src/parsing/handling_dollar2.c \
				src/parsing/ret_utils.c \
				src/parsing/ret_utils2.c 

OBJS			= $(SRCS:.c=.o)

CC				= clang
CFLAGS			= -Wall -Wextra -Werror #-g3 -fsanitize=address
LFLAGS			= -L $(LIBFTDIR) -lft -lreadline
RM				= rm -f

# RULES 

all :			$(NAME)

$(NAME) :		$(OBJS) $(LIBFT)
				$(CC) $(CFLAGS) $(INC) $(OBJS) -o $@ $(LFLAGS)

debug :			$(OBJS) $(LIBFT)
				$(CC) $(CFLAGS) -fsanitize=address $(INC) $(OBJS) -o $@ $(LFLAGS)

$(LIBFT) :		
				$(MAKE) bonus -C $(LIBFTDIR)

.c.o :
				$(CC) $(CFLAGS) $(INC) -c $< -o $(<:.c=.o)

clean :
				$(MAKE) clean -C $(LIBFTDIR)
				$(RM) $(OBJS)

fclean :		clean
				$(MAKE) fclean -C $(LIBFTDIR)
				$(RM) $(NAME)
				$(RM) .*.swp
				$(RM) */.*.swp
				$(RM) */*/.*.swp

re :			clean fclean all

.PHONY :		all clean fclean re
