/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:05:09 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/08/02 16:40:43 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern int exit_status;
int	_execute(t_simple_cmd *cmd, t_data *data)// child process
{
	char *error_str;
	char **path;
	char **env;
	
	error_str = NULL;
	env = list_to_arr(data->env_l);
	path = get_path_env(data->env_l);
	cmd->cmd[0] = cmd_exist(cmd->cmd[0], cmd->cmd_name, path);
	dup_and_close(cmd);
	execve(cmd->cmd[0], cmd->cmd, env);
	// perror("minihell :");
	exit(exit_status);
}

int	handle_cmd(t_simple_cmd *cmd, t_data *data, int *fork_pid)
{
	int pid;

	pid = fork();
	if (!pid)// child 
	{
		// dprintf(2, "pid of this child is %d\n", getpid());
		signal(SIGQUIT, SIG_DFL);
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
	int state;
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
	i = 0;
	
	// while (i < data->cmd_nbr)
	// 	dprintf(2, "pid of command %d\n", data->fork_pid[i++]);
	while (waitpid(data->fork_pid[i++], &state, 0) > 0)
		;
	if (WIFSIGNALED(state))
	{
		exit_status = WTERMSIG(state);
		// printf("sig ==> %d\n", exit_status);
	}
	else if (WIFEXITED(state))
	{
		exit_status = WEXITSTATUS(state);
		// printf("GEN ==> %d\n", exit_status);
	}
	return (0);
}
