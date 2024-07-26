/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:45:52 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/26 18:51:23 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_simple_cmd	*new_cmd_node(t_cmd_limits *cmd)
{
	t_simple_cmd	*new;

	new = malloc(sizeof(t_simple_cmd));
	if (!new)
		return (NULL);
	new->i = 0;
	new->cmd = set_cmd_arr(cmd);// malloc
	new->cmd_name = ft_strdup(new->cmd[0]); // cmd_name is first element
	new->next = NULL;
	new->prev = NULL;
	new->pipe_flag = 0;// how to check pipe flag ?? will set it later
	new->fd.in = 0;// execution part
	new->fd.out = 1;// execution part
	new->pipe[0] = -1;// execution part
	new->pipe[1] = -1;// execution part
	new->redir_num = check_redir(cmd);
	new->redirs = set_redirs(cmd, new->redir_num);
	return (new);
}

t_simple_cmd	*ft_cmd_list(t_cmd_limits *list)
{
	t_simple_cmd	*cmds_list;
	t_simple_cmd	*new_cmd;
	int				i;
	int				cmd_nbr;

	i = 1;
	cmd_nbr = cmd_number(list);
	cmds_list = new_cmd_node(list); //create a node;
	list = list->next;
	while (list)
	{
		new_cmd = new_cmd_node(list);
		new_cmd->i = i++;
		add_back_simple_cmd(&cmds_list, new_cmd); // nedd implementation
		list = list->next;
	}
	set_pipe_flag(cmds_list, cmd_nbr);
	// print_cmds(cmds_list);
	return (cmds_list);
}

void	add_back_simple_cmd(t_simple_cmd **lst, t_simple_cmd *new)
{
	t_simple_cmd	*last;

	if (lst && new)
	{
		if (*lst)
		{
			last = last_cmd(*lst);
			last->next = new;
			new->prev = last;
		}
		else
			*lst = new;
	}
}

t_simple_cmd	*last_cmd(t_simple_cmd *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
