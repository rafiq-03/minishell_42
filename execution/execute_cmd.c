/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:05:09 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/30 12:04:32 by rmarzouk         ###   ########.fr       */
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

int	handle_cmd(t_simple_cmd *cmd, t_data *data)
{
	int pid;

	pid = fork();
	if (!pid)// child 
	{
		handle_here_doc(cmd);
		handle_redirections(cmd);// open 
		if (check_builtin(cmd->cmd_name))
			builtin_cmd(cmd, data, check_builtin(cmd->cmd_name));
		else
			_execute(cmd, data);
	}
	else// parent
	{
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
	while (cmd)
	{
		if (!cmd->next && check_builtin(cmd->cmd_name))// check if there is one builtin
		{
			builtin_cmd(cmd, data, check_builtin(cmd->cmd_name));
			cmd = cmd->next;
			break;
		}
		handle_pipes(cmd);
		handle_cmd(cmd, data);
		cmd = cmd->next;
	}
	wait(NULL);// wati for all forks to finish
	return (0);
}
