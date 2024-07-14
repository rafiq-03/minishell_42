/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:45:52 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/13 19:39:32 by rmarzouk         ###   ########.fr       */
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
	new->cmd = set_cmd_arr(cmd);
	new->cmd_name = ft_strdup(new->cmd[0]); // cmd_name is first element
	new->next = NULL;
	new->prev = NULL;
	new->in_num = check_redir(cmd, REDIR_IN,
			HERE_DOC);// number of redir in
	new->out_num = check_redir(cmd, REDIR_OUT,
			DREDIR_OUT);// number of redir out
	new->pipe_flag = 0;// how to check pipe flag ?? will set it later
	new->fd.in = -1;// execution part
	new->fd.out = -1;// execution part
	new->redir_in = set_redir(cmd, REDIR_IN_FILE, HERE_DOC_LIMITER,
			new->in_num);// fill array with in redir
	new->redir_out = set_redir(cmd, REDIR_OUT_FILE, DREDIR_OUT_FILE,
			new->out_num);// fill array with out redir
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
	print_cmds(cmds_list);
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
