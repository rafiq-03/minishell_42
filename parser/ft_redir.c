/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:40:06 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/09 19:47:56 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_number(t_cmd_limits *cmd)
{
	int i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

char	**fill_cmd(t_cmd_limits *cmd)
{
	char	**cmd_array;
	int		len;
	t_item	*tmp;
	int		i;

	i = 0;
	len = 0;
	tmp = cmd->start;
	while (tmp != cmd->end->next)// must check last limit aka end not end->next
	{
		if (tmp->type == WORD)
			len++;
	}
	cmd_array = malloc(sizeof(char *) * (len + 1));
	if (!cmd_array)
		return (NULL);
	tmp = cmd->start;
	while (tmp != cmd->end->next)// same as above
	{
		if (tmp->type == WORD)
			cmd_array[i++] = ft_strdup(tmp->content);
	}
	cmd_array[i] = NULL;
	return (cmd_array);
}

int	check_redir(t_cmd_limits *cmd,  int	type_1, int	type_2)
{
	t_item	*tmp;
	int		i;

	i = 0;
	tmp = cmd->start;
	while(tmp != cmd->end->next) // must check last limit aka end not end->next
	{
		if (tmp->type == type_1 || tmp->type == type_2)
			i++;
	}
	return (i);
}
t_redir	*fill_redir(t_cmd_limits *cmd, int type1, int type2, int num)
{
	t_item	*tmp;
	t_redir *redir;

	tmp = cmd->start;
	redir = malloc (sizeof(redir) * num);
	if (!redir)
		return (NULL);
	while (tmp != cmd->end->next)
	{
		if (tmp->type == type1)
		{
			redir->type = 1;
			redir->path_or_limiter = ft_strdup(tmp->content);
		}
		else if (tmp->type == type2)
		{
			redir->type = 2;
			redir->path_or_limiter = ft_strdup(tmp->content);
		}
		tmp = tmp->next;
	}
	return (redir);
}

t_simple_cmd *new_cmd_node(t_cmd_limits *cmd)
{
	t_simple_cmd *new;

	new = malloc(sizeof(t_simple_cmd));
	if(!new)
		return (NULL);
	new->cmd = fill_cmd(cmd);
	new->cmd_name = ft_strdup(new->cmd[0]);// cmd_name is first element
	new->next = NULL;
	new->prev = NULL;
	new->in_num = check_redir(cmd, REDIR_IN , HERE_DOC);
	new->out_num = check_redir(cmd, REDIR_OUT, DREDIR_OUT);
	new->pipe_flag = 0;// how to check pipe flag ??
	new->fd.in = -1;// execution part
	new->fd.out = -1;// execution part
	new->redir_in = fill_redir(cmd, REDIR_IN_FILE, HERE_DOC_LIMITER,  new->in_num);
	new->redir_out = fill_redir(cmd, REDIR_OUT_FILE, DREDIR_OUT_FILE, new->out_num);
	return (new);
}

t_simple_cmd	*ft_fill_cmd(t_cmd_limits **list)
{
	t_simple_cmd *cmds_list;
	t_simple_cmd *new_cmd;
	t_cmd_limits *tmp;

	tmp = *list;
	cmds_list = new_cmd_node(tmp); //create a node;
	/*
		implement :
			* cmd name and its options and flags
			* redir if there is
			* pipe if needed
	*/
	
}
