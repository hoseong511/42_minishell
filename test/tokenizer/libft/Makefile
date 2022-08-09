# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/29 11:58:47 by hossong           #+#    #+#              #
#    Updated: 2022/08/09 16:19:31 by hossong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
CFLAGS	= -Wextra -Wall -Werror -g3
AR		= ar
ARFLAGS	= rcs
RM		= rm
RMFLAGS	= -f
SRCS	= ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
		ft_isprint.c ft_tolower.c ft_toupper.c ft_strlen.c \
		ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_memcmp.c ft_strlcpy.c ft_strlcat.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_strnstr.c \
		ft_atoi.c ft_calloc.c ft_strdup.c \
		ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
		ft_substr.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_putnbr.c

OBJS	= $(SRCS:.c=.o)

BONUSSRCS	= ft_lstnew.c ft_lstadd_front.c \
			ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c \
			ft_lstclear.c ft_lstiter.c \
			ft_lstmap.c

BONUSOBJS = $(BONUSSRCS:.c=.o)

HDRS	= .

ifdef WITH_BONUS
	OBJ_FILES = $(OBJS) $(BONUSOBJS)
else
	OBJ_FILES = $(OBJS)
endif

%.o	:	%.c
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I$(HDRS)

all 	:
		@make WITH_BONUS=1 $(NAME)


$(NAME)	:	$(OBJ_FILES)
			$(AR) $(ARFLAGS) $(NAME) $^

#bonus	:
#			@make WITH_BONUS=1

clean	:
			$(RM) $(RMFLAGS) $(OBJS) $(BONUSOBJS)

fclean	:	clean
			$(RM) $(RMFLAGS) $(NAME)

re		:
			@make fclean
			@make all

.PHONY	: clean fclean re all bonus
