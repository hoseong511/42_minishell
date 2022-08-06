NAME	=	cd
CFLAGS	=	-Wextra -Wall -Werror
SRCS	:= 	main.c
OBJS	:= $(SRCS:.c=.o)

%.o	: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all			:
				@make $(NAME)

$(NAME)		:	$(OBJS)
				$(CC) $(CFLAGS) $^ -o $@

clean		:	
				$(RM) $(RMFLAGS) $(OBJS) $(OBJS_B)

fclean		:	clean
				$(RM) $(RMFLAGS) $(NAME)

re			:
				@make fclean
				@make all

.PHONY		:	clean fclean re all
