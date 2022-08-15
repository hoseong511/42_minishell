# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/07 14:34:58 by hossong           #+#    #+#              #
#    Updated: 2022/08/14 15:45:50 by namkim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CFLAGS 	=	-Wall -Wextra -Werror -g3

LIB		=	-L$(HOME)/.brew/opt/readline/lib -lreadline -L ./lib/libft -lft
LIBFT	=	lib/libft/libft.a

INCLUDE =	-I$(HOME)/.brew/opt/readline/include -I ./includes
SRCS_DIR = srcs/
SRCS_FILES = main.c pre_syntax.c env.c error.c init.c parser.c tokenizer.c utils.c\
			ctrl_list.c bind_type.c replacement.c
SRCS	=	$(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS	=	$(SRCS:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@ $(INCLUDE)

all		:
	@make -C $(dir $(LIBFT))
	@make $(NAME)

$(NAME)	: $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ $(LIB)

clean	:
	$(RM) $(OBJS)
	@make -C $(dir $(LIBFT)) clean

fclean	:	clean
	$(RM) $(NAME)
	@make -C $(dir $(LIBFT)) fclean

re	:
	@make fclean
	@make all

.PHONY	: all clean fclean re

