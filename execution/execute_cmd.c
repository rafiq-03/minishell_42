/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:05:09 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/27 13:03:40 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	handle_pipes(t_simple_cmd *cmd)
{
	//if there is pipe or not : [0 = no pipe]  [1 = before] [2 = after] [3 = befor & after]
	if (cmd->pipe_flag == AFTER_PIPE)// before
	{
		// printf("the pipe is before the command\n");
		cmd->fd.in = cmd->prev->pipe[0]; // or prev->pipe[1];
		// printf("previos command is %s\n", cmd->prev->cmd_name);
	}
	else if (cmd->pipe_flag == BEFORE_PIPE)// after
	{
		// printf("the pipe is after the command\n");
		if (pipe(cmd->pipe) == -1)
			return(1);
		// printf("before\n");
		// printf("\npipe entries = [ %d | %d ]\n\n", cmd->pipe[0], cmd->pipe[1]);
		cmd->fd.out = cmd->pipe[1]; // or cmd->pipe[0]
	}
	else if (cmd->pipe_flag == BETWEEN_PIPES)// between
	{
		// printf("the pipe is between commands\n");
		if (pipe(cmd->pipe) == -1)
			return(1);
		// printf("\npipe entries = [ %d | %d ]\n\n", cmd->pipe[0], cmd->pipe[1]);
		cmd->fd.in = cmd->prev->pipe[0];
		cmd->fd.out = cmd->pipe[1];
	}
	return (0);
}

int	_execute(t_simple_cmd *cmd, t_data *data)
{
	(void)data;
	print_cmd(cmd);
	return (0);
}

int	handle_cmd(t_simple_cmd *cmd, t_data *data)
{
	int pid;

	pid = fork();
	if (!pid)
	{
		handle_here_doc(cmd);
		handle_redirections(cmd);
		if (check_builtin(cmd->cmd_name))
			builtin_cmd(cmd, data, check_builtin(cmd->cmd_name));
		else
			_execute(cmd, data);
		close_all_fds(cmd);
	}
	else
	{
		printf("\t\twaiting for child..\n");
		wait(NULL);
	}
	return (0);
}

int	execute_cmd(t_simple_cmd *cmd, t_data *data)
{
	while (cmd)
	{
		handle_pipes(cmd);
		handle_cmd(cmd, data);
		if (cmd->pipe_flag == AFTER_PIPE || cmd->pipe_flag == BETWEEN_PIPES)// close unused pipes
		{
			close(cmd->prev->pipe[0]);
			close(cmd->prev->pipe[1]);
			printf("close pipe [%d, %d]\n", cmd->prev->pipe[0], cmd->prev->pipe[1]);
		}
		cmd = cmd->next;
	}
	return (0);
}
