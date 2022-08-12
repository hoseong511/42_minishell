name = bind
CFLAGS = -Wall -Werror -Wextra -g3
srcs = bind_type.c error.c dummy.c
OBJS := $(srcs:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@ -I.

all :
	@make -C libft
	@make $(name)

$(name) : $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) $^ -o $@ -L ./libft -lft

clean :
	$(RM) $(OBJS) $(name)
	@make -C libft fclean

re	:
	@make clean
	@make
	