/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:40:06 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/26 09:49:13 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	cmd_number(t_cmd_limits *cmd) // number of commands
{
	int	i;

	i = 0;
	while (cmd)
	{
		cmd = cmd->next;
		i++;
	}
	return (i);
}

int	array_len(t_cmd_limits *cmd)
{
	int		len;
	t_item	*tmp;

	len = 0;
	tmp = cmd->start;
	while (tmp != cmd->end->next) //must check last limit aka end not end->next
	{
		if (tmp->type == WORD)
			len++;
		tmp = tmp->next;
	}
	return (len);
}

char	**set_cmd_arr(t_cmd_limits *cmd) //cmd array aka command and its options
{
	char	**cmd_array;
	int		len;
	t_item	*tmp;
	int		i;

	i = 0;
	len = 0;
	tmp = cmd->start;
	len = array_len(cmd);
	// printf("len = %d\n", len);
	cmd_array = (char **)malloc(sizeof(char *) * (len + 1)); // malloc
	if (!cmd_array)
		return (NULL);
	while (tmp != cmd->end->next) // same as above
	{
		if (tmp->type == WORD)
			cmd_array[i++] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	cmd_array[i] = NULL;
	return (cmd_array);
}

int	check_redir(t_cmd_limits *cmd) //nbr of type
{
	t_item	*tmp;
	int		i;

	i = 0;
	tmp = cmd->start;
	while (tmp != cmd->end->next) //must check last limit aka end not end->next
	{
		if (tmp->type == REDIR_IN || tmp->type == HERE_DOC
			|| tmp->type == REDIR_OUT || tmp->type == DREDIR_OUT)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
t_redir	*set_redirs(t_cmd_limits *cmd, int num)
{
	t_item	*tmp;
	t_redir	*redir;
	int		i;

	i = 0;
	tmp = cmd->start;
	redir = malloc(sizeof(t_redir) * num);
	if (!redir)
		return (NULL);
	while (tmp != cmd->end->next)
	{
		if (tmp->type == REDIR_IN_FILE || tmp->type == REDIR_OUT_FILE
			|| tmp->type == DREDIR_OUT_FILE || tmp->type == HERE_DOC_LIMITER)
		{
			redir[i].type = tmp->type;
			redir[i++].path_or_limiter = ft_strdup(tmp->content);
		}
		tmp = tmp->next;
	}
	// printf("number of redirs filled = %d\n", i);
	return (redir);
}

void	set_pipe_flag(t_simple_cmd *head, int cmd_nbr)
{
	if (cmd_nbr == 1)
		return ;
	while (head)
	{
		if (head->i == 0)
			head->pipe_flag = 2; // after
		else if (head->i == cmd_nbr - 1)
			head->pipe_flag = 1; // before
		else
			head->pipe_flag = 3; // before and after
		head = head->next;
	}
}
