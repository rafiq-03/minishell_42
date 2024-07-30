/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:28:17 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/30 15:05:53 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char **get_path_env(t_env *env_l)
{
	while (env_l)
	{
		if (!ft_strncmp(env_l->key, "PATH", 4))
			return (ft_split(env_l->value, ':'));
		env_l = env_l->next;
	}
	return (NULL);
}

char **list_to_arr(t_env *tmp)
{
	int i = 0;
	int	len = 0;
	char **env;
	t_env *env_l = tmp;
	while (tmp)
	{
		len++;
		tmp=tmp->next;
	}
	env = malloc (sizeof(char **) * (len + 1));
	i = 0;
	while (env_l && i < len)
	{
		if (env_l->value_falg)
		env[i++] = ft_strjoin(ft_strdup(env_l->key), ft_strdup(env_l->value));
	}
	env[i] = NULL;
	return (env);
}

int	close_all_fds(t_simple_cmd *cmd)
{
	int i;

	i = 0;
	while (i < cmd->redir_num)
	{
		if (cmd->redirs[i].fd != 0 && cmd->redirs[i].fd != 1)
		{
			// dprintf(2, "close fd = %d\n", cmd->redirs[i].fd);
			close(cmd->redirs[i].fd);
		}
		i++;
	}
	return (0);
}

int	last_redir(t_redir *redir, int len, int type, int last_fd)
{
	int	i;
	
	i = 0;
	while (i  < len)
	{
		if (type == REDIR_IN)
		{
			if (redir[i].type == REDIR_IN_FILE)
				last_fd = redir[i].fd;
			// else if (redir[i].type == HERE_DOC_LIMITER)
			// 	last_fd = redir[i].fd;
		}
		else if (type == REDIR_OUT)
		{
			if (redir[i].type == REDIR_OUT_FILE)
				last_fd = redir[i].fd;
			else if (redir[i].type == DREDIR_OUT_FILE)
				last_fd = redir[i].fd;
		}
		i++;
	}
	return (last_fd);
}
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
int handle_here_doc(t_simple_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd->redir_num)
	{
		if (cmd->redirs[i].type == HERE_DOC_LIMITER)
		{
			cmd->redirs[i].fd = open("/tmp/here_doc_test", O_RDWR | O_CREAT , 0666);
			
			printf("here_doce fd = %d\n", cmd->redirs[i].fd);
		}
	}
	return (0);
}
int handle_redirections(t_simple_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->redir_num)
	{
		if (cmd->redirs[i].type == REDIR_IN_FILE)
		{
			cmd->redirs[i].fd = open(cmd->redirs[i].path_or_limiter, O_RDWR);
			// dprintf(2, "fd = %d -> open (%s) \n", cmd->redirs[i].fd, cmd->redirs[i].path_or_limiter);
		}
		else if (cmd->redirs[i].type == REDIR_OUT_FILE)
		{
			cmd->redirs[i].fd = open(cmd->redirs[i].path_or_limiter, O_RDWR | O_CREAT | O_TRUNC , 0644);
			// dprintf(2, "fd = %d -> open (%s) \n", cmd->redirs[i].fd, cmd->redirs[i].path_or_limiter);
		}
		else if (cmd->redirs[i].type == DREDIR_OUT_FILE)
		{
			cmd->redirs[i].fd = open(cmd->redirs[i].path_or_limiter, O_RDWR | O_CREAT | O_APPEND, 0644);
			// dprintf(2, "fd = %d -> open (%s) \n", cmd->redirs[i].fd, cmd->redirs[i].path_or_limiter);
		}
		i++;
	}
	cmd->fd.in = last_redir(cmd->redirs, cmd->redir_num, REDIR_IN, cmd->fd.in);
	cmd->fd.out = last_redir(cmd->redirs, cmd->redir_num, REDIR_OUT, cmd->fd.out);
	return (0);
}

int	dup_and_close(t_simple_cmd *cmd)
{
		if (cmd->fd.in != 0)
	{
		dup2(cmd->fd.in, STDIN_FILENO);
		// dprintf(2, "\n                             dup fd.in %d\n", cmd->fd.in);
	}
	if (cmd->fd.out != 1)
	{
		dup2(cmd->fd.out, STDOUT_FILENO);
		// dprintf(2, "\n                             dup fd.out %d\n", cmd->fd.out);
	}
	if (cmd->pipe_flag == AFTER_PIPE || cmd->pipe_flag == BETWEEN_PIPES)// close unused pipes in child process
	{
		close(cmd->prev->pipe[0]);
		close(cmd->prev->pipe[1]);
		// dprintf(2, "close pipe [%d, %d] in child\n", cmd->prev->pipe[0], cmd->prev->pipe[1]);
	}
	close_all_fds(cmd);
	return (0);
}

int	handle_pipes(t_simple_cmd *cmd)
{
	//if there is pipe or not : [0 = no pipe]  [1 = before] [2 = after] [3 = befor & after]
	if (cmd->pipe_flag == AFTER_PIPE)// before
	{
		cmd->fd.in = cmd->prev->pipe[0]; // or prev->pipe[1];
	}
	else if (cmd->pipe_flag == BEFORE_PIPE)// after
	{
		pipe(cmd->pipe);
		// printf("\npipe entries = [ %d | %d ]\n\n", cmd->pipe[0], cmd->pipe[1]);
		cmd->fd.out = cmd->pipe[1]; // or cmd->pipe[0]
	}
	else if (cmd->pipe_flag == BETWEEN_PIPES)// between
	{
		pipe(cmd->pipe);
		// printf("\npipe entries = [ %d | %d ]\n\n", cmd->pipe[0], cmd->pipe[1]);
		cmd->fd.in = cmd->prev->pipe[0];
		cmd->fd.out = cmd->pipe[1];
	}
	return (0);
}

char *cmd_exist(char *cmd_name, char **path, bool *exist)
{
	// int flag;
	int	i;
	char *tmp;
	// struct stat cmd_info;

	tmp=ft_strjoin(ft_strdup("/"), cmd_name);
	
	i = 0;
	while (path[i])
	{
		cmd_name = ft_strjoin(ft_strdup(path[i]), ft_strdup(tmp));
		
		// flag = stat(cmd_name, &cmd_info);
		// if (flag == -1)
		// 	return (NULL);
		// if (S_ISREG(cmd_info.st_mode) && S)
		
		if (!access(cmd_name, X_OK))
		{
			*exist = true;
			return (cmd_name);
		}
		i++;
	}
	return (NULL);
}
