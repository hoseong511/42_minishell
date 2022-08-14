# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/07 14:34:58 by hossong           #+#    #+#              #
#    Updated: 2022/08/14 18:12:51 by hossong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	mini
CFLAGS 	=	-Wall -Wextra -Werror -g3

LIB		=	 -lreadline -L ./lib/libft -lft
LIBFT	=	lib/libft/libft.a

INCLUDE =	 -I ./includes
SRCS_DIR = srcs/
SRCS_FILES = main.c pre_syntax.c env.c error.c init.c parser.c tokenizer.c \
			ctrl_list.c bind_type.c ctrl_excution.c ctrl_free.c
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

