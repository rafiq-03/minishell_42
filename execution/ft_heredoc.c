/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:34:18 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/08/04 10:47:36 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	heredoc_nbr(t_simple_cmd *cmd)// heredoc nbr in one command;
{
	int	nbr;
	int	i;

	nbr = 0;
	i = 0;
	while (i < cmd->redir_num)
	{
		if (cmd->redirs[i].type == HERE_DOC_LIMITER)
			nbr++;
		i++;
	}
	return (nbr);
}

int	heredocs_array(t_simple_cmd *cmd) // heredoce arr one array per command
{
	int i;
	int id;

	while (cmd)
	{
		cmd->heredoc_nbr = heredoc_nbr(cmd);
		cmd->heredoc_arr = malloc(sizeof(char *) * (cmd->heredoc_nbr + 1));// must be freed
		id = 0;
		i = 0;
		while (i < cmd->redir_num)
		{
			if (cmd->redirs[i].type == HERE_DOC_LIMITER)
				cmd->heredoc_arr[i] = ft_strjoin(ft_strdup("/tmp/heredoc_"),
					ft_strjoin(ft_itoa(cmd->i), ft_itoa(id++)));
			i++;
		}
		cmd = cmd->next;
	}
	return (0);
}

int handle_all_heredocs(t_simple_cmd *cmd)
{
	int pid;

	heredocs_array(cmd);
	pid = fork();
	if (pid == 0)
	{
		while (cmd)
		{
			handle_here_doc(cmd);
			cmd = cmd->next;
		}
		exit(0);
	}
	else
		wait(NULL);// check it
	return (0);
}

int handle_here_doc(t_simple_cmd *cmd)
{
	int	i;
	int	fd;
	char *line;
	int		id;

	id = 0;
	i = -1;
	while (++i < cmd->redir_num)
	{
		if (cmd->redirs[i].type == HERE_DOC_LIMITER)
		{
			fd = open(cmd->heredoc_arr[id++], O_RDWR | O_CREAT | O_TRUNC, 0666);
			if (fd == -1)
				perror("minishell :heredoc :");
			line = readline("> ");
			while(line)
			{
				if (!ft_strcmp(line, cmd->redirs[i].path_or_limiter))
				{
					free(line);
					break;
				}
				write(fd, line, ft_strlen(line));
				write(fd, "\n", 1);
				free(line);
				line = readline("> ");
			}
			close(fd);
		}
	}
	return (0);
}
