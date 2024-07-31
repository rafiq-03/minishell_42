/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:05:09 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/31 12:39:12 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	_execute(t_simple_cmd *cmd, t_data *data)// child process
{
	char **path = get_path_env(data->env_l);
	char **env = list_to_arr(data->env_l);
	bool exist;
	exist = false;
	cmd->cmd[0] = cmd_exist(cmd->cmd[0], path, &exist);
	dup_and_close(cmd);
	// print_cmd(cmd);
	execve(cmd->cmd[0], cmd->cmd, env);
	printf("exeve doesn't work\n");
	exit(1);
}

int	handle_cmd(t_simple_cmd *cmd, t_data *data, int *fork_pid)
{
	int pid;

	pid = fork();
	if (!pid)// child 
	{
		// dprintf(2, "pid of this child is %d\n", getpid());
		handle_here_doc(cmd);
		handle_redirections(cmd);// open 
		if (check_builtin(cmd->cmd_name))
			builtin_cmd(cmd, data, check_builtin(cmd->cmd_name), false);
		else
			_execute(cmd, data);
	}
	else// parent
	{
		*fork_pid = pid;
		if (cmd->pipe_flag == AFTER_PIPE || cmd->pipe_flag == BETWEEN_PIPES)// close unused pipes in parent process
		{
			close(cmd->prev->pipe[0]);
			close(cmd->prev->pipe[1]);
			// printf("close pipe [%d, %d] in parent\n", cmd->prev->pipe[0], cmd->prev->pipe[1]);
		}
	}
	return (0);
}

int	execute_cmd(t_simple_cmd *cmd, t_data *data)
{
	int i;
	bool	flag;

	i = 0;
	flag = false;
	data->fork_pid = malloc(data->cmd_nbr * sizeof(int));// must be freed
	if (!cmd->next && check_builtin(cmd->cmd_name))// check if there is one builtin
	{
		flag = true;
		handle_here_doc(cmd);
		handle_redirections(cmd);
		builtin_cmd(cmd, data, check_builtin(cmd->cmd_name), flag);
		return (0);
	}
	while (cmd)
	{
		handle_pipes(cmd);
		handle_cmd(cmd, data, &data->fork_pid[i++]);
		cmd = cmd->next;
	}
	// i = 0;
	// while (i < data->cmd_nbr)
	// 	dprintf(2, "pid of command %d\n", data->fork_pid[i++]);
	while (wait(NULL) > 0)
		;
	return (0);
}
