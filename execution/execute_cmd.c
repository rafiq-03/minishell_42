/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:05:09 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/26 18:56:47 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*search_cmd_path(char **split_path, char *cmd_name, bool *flag)
{
	int i;

	char *cmd;
	char *tmp = ft_strjoin(ft_strdup("/"), ft_strdup(cmd_name));
	i = 0;
	while (split_path[i])
    {
        cmd = ft_strjoin(ft_strdup(split_path[i]), ft_strdup(tmp));
        if (!access(cmd, X_OK))
		{
			*flag = 1;
			return (cmd);
		}
		i++;
    }
	return (cmd_name);
}

int	handle_pipes(t_simple_cmd *cmd)
{
	//if there is pipe or not : [0 = no pipe]  [1 = before] [2 = after] [3 = befor & after]
	if (cmd->pipe_flag == 1)// before
	{
		printf("the pipe is before the command\n");
		cmd->fd.in = cmd->prev->pipe[0]; // or prev->pipe[1];
		// printf("previos command is %s\n", cmd->prev->cmd_name);
	}
	else if (cmd->pipe_flag == 2)// after
	{
		printf("the pipe is after the command\n");
		if (pipe(cmd->pipe) == -1)
			return(1);
		printf("before\n");
		printf("\npipe entries = [ %d | %d ]\n\n", cmd->pipe[0], cmd->pipe[1]);
		cmd->fd.out = cmd->pipe[1]; // or cmd->pipe[0]
	}
	else if (cmd->pipe_flag == 3)// between
	{
		printf("the pipe is between commands\n");
		if (pipe(cmd->pipe) == -1)
			return(1);
		cmd->fd.in = cmd->prev->pipe[0];
		cmd->fd.out = cmd->pipe[1];
	}
	return (0);
}

int handle_here_doc(t_simple_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd->redir_num)
	{
		if (cmd->redirs[i].type == HERE_DOC_LIMITER)
		{
			printf("here_doce\n");
		}
	}
	return (0);
}
int handle_redirections(t_simple_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd->redir_num)
	{
		if (cmd->redirs[i].type == REDIR_IN_FILE)
		{
			cmd->fd.in = open(cmd->redirs[i].path_or_limiter, O_RDONLY);
			if (cmd->fd.in == -1)
			{
				printf("problem in opne file\n");
				return (1);
			}
		}
		else if (cmd->redirs[i].type == REDIR_OUT_FILE)
			cmd->fd.out = open(cmd->redirs[i].path_or_limiter, O_RDWR | O_CREAT);
		else if (cmd->redirs[i].type == REDIR_OUT_FILE)
			cmd->fd.out = open(cmd->redirs[i].path_or_limiter, O_RDWR | O_CREAT | O_APPEND);
	}
	if (cmd->fd.out == -1)
		printf("there is a problem\n");
	return (0);
}
int	_execute(t_simple_cmd *cmd, t_data *data)
{
	int pid;
	char **split_path;
	char **env;
	bool flag;
	
	handle_pipes(cmd);
	handle_here_doc(cmd);
	handle_redirections(cmd);
	// printf("fd.in  %d\n", cmd->fd.in);
	// printf("fd.out %d\n", cmd->fd.out);
	dup2(1, cmd->fd.out);
	dup2(0, cmd->fd.in);
	// close(1);
	// close(0);
	flag = 0;
	env = list_to_arr(data->env_l);
	split_path = get_path_env(data->env_l);
	if (!split_path)
		return (1);
	cmd->cmd[0] = search_cmd_path(split_path, cmd->cmd[0], &flag);
	if (flag == false)
	{
    	printf("%s : command not found\n", cmd->cmd_name);
		return (0);
	}
	pid = fork();
	if (!pid)
		execve(cmd->cmd[0], cmd->cmd, env);
	else
	{
		if (cmd->pipe_flag != 0)
		{
			close(cmd->fd.in);
			close(cmd->fd.out);
		}
		wait(NULL);
	}
	
	return (0);
}

int	execute_cmd(t_simple_cmd *cmd, t_data *data)
{
	while (cmd)
	{
		// here we will open fds and pipes	
		if (check_builtin(cmd->cmd_name))
			builtin_cmd(cmd, data, check_builtin(cmd->cmd_name));
		else
			_execute(cmd, data);
		cmd = cmd->next;
	}
	return (0);
}
