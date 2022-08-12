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
	t_cmd	*new;
	t_list	*tmp;

	tmp = NULL;
	new = init_cmdnode("cat", ARGS);
	ft_lstadd_back(&tmp, ft_lstnew(new));
	data->cmdlist = tmp;
	//insert_dummy(&data->cmdlist, ft_strdup("cat"), ARGS);


	// new = init_cmdnode("cat", ARGS);
	// ft_lstadd_back(&data->cmdlist, ft_lstnew(new));

	// new = init_cmdnode("<", R_IN);
	// ft_lstadd_back(&data->cmdlist, ft_lstnew(new));

	// new = init_cmdnode("txt.c", R_IN);
	// ft_lstadd_back(&data->cmdlist, ft_lstnew(new));

	// new = init_cmdnode("<<", R_HEREDOC);
	// ft_lstadd_back(&data->cmdlist, ft_lstnew(new));

	// new = init_cmdnode("txt.c", R_IN);
	// ft_lstadd_back(&data->cmdlist, ft_lstnew(new));

	// new = init_cmdnode("|", PIPE);
	// ft_lstadd_back(&data->cmdlist, ft_lstnew(new));

	// new = init_cmdnode("grep", ARGS);
	// ft_lstadd_back(&data->cmdlist, ft_lstnew(new));

	// new = init_cmdnode("a", ARGS);
	// ft_lstadd_back(&data->cmdlist, ft_lstnew(new));
}
