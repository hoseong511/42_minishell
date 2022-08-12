#include "bind_type.h"

static t_cmd	*init_cmdnode(char *str, t_type type)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		ft_error("Malloc error\n");
	new->str = ft_strdup(str);
	new->type = type;
	return (new);
}

void	dummy_data(t_data *data)
{
	t_cmd	*new;

	new = init_cmdnode("cat", ARGS);
	ft_lstadd_back(&data->cmdlist, ft_lstnew(new));

	new = init_cmdnode("<", R_IN);
	ft_lstadd_back(&data->cmdlist, ft_lstnew(new));

	new = init_cmdnode("txt.c", R_IN);
	ft_lstadd_back(&data->cmdlist, ft_lstnew(new));

	new = init_cmdnode("<<", R_HEREDOC);
	ft_lstadd_back(&data->cmdlist, ft_lstnew(new));

	new = init_cmdnode("txt.c", R_IN);
	ft_lstadd_back(&data->cmdlist, ft_lstnew(new));

	new = init_cmdnode("|", PIPE);
	ft_lstadd_back(&data->cmdlist, ft_lstnew(new));

	new = init_cmdnode("grep", ARGS);
	ft_lstadd_back(&data->cmdlist, ft_lstnew(new));

	new = init_cmdnode("a", ARGS);
	ft_lstadd_back(&data->cmdlist, ft_lstnew(new));
}
