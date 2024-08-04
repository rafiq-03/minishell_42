/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:05:09 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/08/04 12:44:57 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern int g_exit_status;
int	_execute(t_simple_cmd *cmd, t_data *data)// child process
{
	char *error_str;
	char **path;
	char **env;
	
	error_str = NULL;
	env = list_to_arr(data->env_l);
	path = get_path_env(data->env_l);
	if (!cmd->cmd[0])
		exit(0);
	cmd->cmd[0] = cmd_exist(cmd->cmd[0], cmd->cmd_name, path);
	dup_and_close(cmd);
	execve(cmd->cmd[0], cmd->cmd, env);
	exit(g_exit_status);
}

int	handle_cmd(t_simple_cmd *cmd, t_data *data, int *fork_pid)
{
	int pid;

	signal (SIGINT, SIG_IGN);
	pid = fork();
	if (!pid)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		handle_redirections(cmd);// open
		if (check_builtin(cmd->cmd_name))
			builtin_cmd(cmd, data, check_builtin(cmd->cmd_name), false);
		else
			_execute(cmd, data);
	}
	else
	{
		*fork_pid = pid;
		if (cmd->pipe_flag == AFTER_PIPE || cmd->pipe_flag == BETWEEN_PIPES)
		{
			close(cmd->prev->pipe[0]);
			close(cmd->prev->pipe[1]);
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
	if (!cmd->next && check_builtin(cmd->cmd_name))
	{
		flag = true;
		handle_here_doc(cmd);
		handle_redirections(cmd);
		builtin_cmd(cmd, data, check_builtin(cmd->cmd_name), flag);
		return (0);
	}
	if (handle_all_heredocs(cmd, &state))
	{
		g_exit_status = EXIT_FAILURE;
		return (1);
	}
	while (cmd)
	{
		handle_pipes(cmd);
		handle_cmd(cmd, data, &data->fork_pid[i++]);
		cmd = cmd->next;
	}
	i = 0;
	while (waitpid(data->fork_pid[i++], &state, 0) > 0 && i < data->cmd_nbr)
		;
	if (WIFSIGNALED(state))
		g_exit_status = WTERMSIG(state) + 128;
	else if (WIFEXITED(state))
		g_exit_status = WEXITSTATUS(state);
	signal(SIGINT, handle_sigint);
	return (0);
}
