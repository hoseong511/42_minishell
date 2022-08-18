# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/07 14:34:58 by hossong           #+#    #+#              #
#    Updated: 2022/08/18 19:54:10 by hossong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CFLAGS 	=	-Wall -Wextra -Werror -g3#-fsanitize=address

LIB		=	 -lreadline -L ./lib/libft -lft
LIBFT	=	lib/libft/libft.a

INCLUDE =	 -I ./includes
SRCS_DIR = srcs/
SRCS_FILES = main.c pre_syntax.c error.c init.c parser.c tokenizer.c utils.c \
			ctrl_list.c bind_type.c replacement.c ctrl_free.c ctrl_execution.c \
			exec_utils.c ctrl_env1.c ctrl_env2.c ctrl_env1.c ctrl_env2.c \
			replacement_utils.c ctrl_process.c redirections.c ctrl_pipe.c

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

