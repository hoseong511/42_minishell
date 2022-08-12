#include "bind_type.h"

static t_cmd	*init_cmdnode(char *str, t_type type)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		ft_error("Malloc error\n");
	new->str = str;
	new->type = type;
	return (new);
}

void	insert_dummy(t_list **cmdlist, char *str, t_type type)
{
	t_cmd	*new;

	new = init_cmdnode(str, type);
	ft_lstadd_back(cmdlist, ft_lstnew(new));
}

void	dummy_data(t_data *data)
{
	insert_dummy(&data->cmdlist, "cat", ARGS);
	insert_dummy(&data->cmdlist, "<", R_IN);
	insert_dummy(&data->cmdlist, "txt.c", R_IN);
	insert_dummy(&data->cmdlist, "<<", R_HEREDOC);
	insert_dummy(&data->cmdlist, "txt.c", R_HEREDOC);
	insert_dummy(&data->cmdlist, "|", PIPE);
	insert_dummy(&data->cmdlist, "grep", ARGS);
	insert_dummy(&data->cmdlist, "a", ARGS);
	insert_dummy(&data->cmdlist, ">", R_HEREDOC);
	insert_dummy(&data->cmdlist, "a", R_HEREDOC);
}
