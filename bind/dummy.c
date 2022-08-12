#include "bind_type.h"

static t_cmdnode	*init_cmdnode(char *str, t_type type)
{
	t_cmdnode	*new;

	new = (t_cmdnode *)malloc(sizeof(t_cmdnode));
	if (!new)
		ft_error("Malloc error\n");
	new->str = ft_strdup(str);
	new->type = type;
	return (new);
}

void	dummy_data(t_data *data)
{
	t_cmdnode	*new;

	new = init_cmdnode("cat", t_argv);
	ft_lstadd_back(&data->cmdlist, ft_lstnew(new));

	new = init_cmdnode("<", t_less);
	ft_lstadd_back(&data->cmdlist, ft_lstnew(new));

	new = init_cmdnode("txt.c", t_less);
	ft_lstadd_back(&data->cmdlist, ft_lstnew(new));

	new = init_cmdnode("|", t_pipe);
	ft_lstadd_back(&data->cmdlist, ft_lstnew(new));

	new = init_cmdnode("grep", t_argv);
	ft_lstadd_back(&data->cmdlist, ft_lstnew(new));

	new = init_cmdnode("a", t_argv);
	ft_lstadd_back(&data->cmdlist, ft_lstnew(new));
}
