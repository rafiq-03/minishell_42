/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:07:43 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/22 16:12:46 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_lst(t_cmd_limits *lst)
{
	t_cmd_limits	*tmp;
	t_item			*tm;

	tmp = lst;
	while (tmp)
	{
		tm = tmp->start;
		printf("**************************************\n\n");
		while (tm != tmp->end)
		{
			printf("[%s]\t", tm->content);
			tm = tm->next;
		}
		printf("[%s]\t", tm->content);
		printf("\n");
		tmp = tmp->next;
	}
	printf("\n**************************************\n");
}

void	print(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("\033[0;33m|  %s  \033[0m", str[i++]);
	}
	printf("\033[0;33m|  NULL  |\033[0m\n\n");
}

void	print_redir(t_redir *redir, int type, int num)
{
	int	i;

	i = 0;
	(void)type;
	if (type == 1)
		printf("\n* redirection in :\n");
	else if (type == 2)
		printf("\n* redirection out :\n");
	if (num == 0)
		printf("\t|no redir|\n");
	while (i < num)
	{
		printf("\t-> type : %d\t", redir[i].type);
		printf("path : %s\n", redir[i].path_or_limiter);
		i++;
	}
}

void	print_cmd(t_simple_cmd *cmd)
{
	printf("\033[0;32m=============================================================\033[0m\n\n");
	printf("[%d] => Command name	: %s\n\n",cmd->i, cmd->cmd_name);
	print(cmd->cmd);
	if (cmd->pipe_flag == 2)
		printf("pipe flag	: after\n");
	else if (cmd->pipe_flag == 1)
		printf("pipe flag	: before\n");
	else if (cmd->pipe_flag == 3)
		printf("pipe flag	: between\n");
	else
		printf("pipe flag	: no pipe\n");
	print_redir(cmd->redir_in, 1, cmd->in_num);
	print_redir(cmd->redir_out, 2, cmd->out_num);
	printf("\n\033[0;32m=============================================================\033[0m\n");
}

void	print_cmds(t_simple_cmd *cmd)
{
	while (cmd)
	{
		print_cmd(cmd);
		cmd = cmd->next;
	}
}
// "\033[0;32m\033[0m"
// "\033[0;%s\033[0m"
