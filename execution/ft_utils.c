/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:28:17 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/27 13:10:51 by rmarzouk         ###   ########.fr       */
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
		printf("close fd = %d\n", cmd->redirs[i].fd);
		close(cmd->redirs[i].fd);
		i++;
	}
	close(cmd->here_doc_pipe[0]);
	close(cmd->here_doc_pipe[1]);
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
		}
		else if (type == REDIR_OUT)
		{
			if (redir[i].type == REDIR_OUT_FILE)
				last_fd = redir[i].fd;
			if (redir[i].type == DREDIR_OUT_FILE)
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
			printf("here_doce\n");
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
			printf("fd = %d -> open (%s) \n", cmd->redirs[i].fd, cmd->redirs[i].path_or_limiter);
		}
		else if (cmd->redirs[i].type == REDIR_OUT_FILE)
		{
			cmd->redirs[i].fd = open(cmd->redirs[i].path_or_limiter, O_RDWR | O_CREAT, 0666);
			printf("fd = %d -> open (%s) \n", cmd->redirs[i].fd, cmd->redirs[i].path_or_limiter);
		}
		else if (cmd->redirs[i].type == REDIR_OUT_FILE)
		{
			cmd->redirs[i].fd = open(cmd->redirs[i].path_or_limiter, O_RDWR | O_CREAT | O_APPEND, 0666);
			printf("fd = %d -> open (%s) \n", cmd->redirs[i].fd, cmd->redirs[i].path_or_limiter);
		}
		i++;
	}
	cmd->fd.in = last_redir(cmd->redirs, cmd->redir_num, REDIR_IN, cmd->fd.in);
	cmd->fd.out = last_redir(cmd->redirs, cmd->redir_num, REDIR_OUT, cmd->fd.out);
	return (0);
}
