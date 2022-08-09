NAME = exe
CFLAGS = -Wall -Werror -Wextra -g3
HDRS = -I libft
SRCS = main.c tokenizer.c error.c env.c
OBJS = $(SRCS:.c=.o)
LIB = -L libft -lft

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@ $(HDRS)
	
all :
	@make -C libft
	@make $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIB)

clean :
	$(RM) $(OBJS) $(NAME)

re :
	@make clean
	@make
	
