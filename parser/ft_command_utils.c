/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:40:06 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/13 17:04:43 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		cmd_number(t_cmd_limits *cmd)// number of commands
{
	int i;

	i = 0;
	while (cmd)
	{
		cmd = cmd->next;
		i++;
	}
	return (i);
}

char	**set_cmd_arr(t_cmd_limits *cmd)// command array aka command and its options
{
	char	**cmd_array;
	int		len;
	t_item	*tmp;
	int		i;

	i = 0;
	len = 0;
	tmp = cmd->start;
	while (tmp != cmd->end->next)// must check last limit aka end not end->next
	{
		if (tmp->type == WORD)
			len++;
		tmp = tmp->next;
	}
	cmd_array = malloc(sizeof(char *) * (len + 1));
	if (!cmd_array)
		return (NULL);
	tmp = cmd->start;
	while (tmp != cmd->end->next)// same as above
	{
		if (tmp->type == WORD)
			cmd_array[i++] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	cmd_array[i] = NULL;
	return (cmd_array);
}

int		check_redir(t_cmd_limits *cmd,  int	type_1, int	type_2) // check redirections numbers of a type
{
	t_item	*tmp;
	int		i;

	i = 0;
	tmp = cmd->start;
	while(tmp != cmd->end->next) // must check last limit aka end not end->next
	{
		if (tmp->type == type_1 || tmp->type == type_2)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

t_redir	*set_redir(t_cmd_limits *cmd, int type1, int type2, int num)
{
	t_item	*tmp;
	t_redir *redir;
	int	i;

	i = 0;
	tmp = cmd->start;
	redir = malloc (sizeof(t_redir) * num);
	if (!redir)
		return (NULL);
	while (tmp != cmd->end->next)
	{
		if (tmp->type == type1)// redir_in or redir_out
		{
			redir[i].type = 1;//< or > 
			redir[i].path_or_limiter = ft_strdup(tmp->content);
			printf("%d\n", tmp->type);
			printf("%d\n", REDIR_OUT_FILE);
			printf("redir type %d\n", redir[i].type);
			printf("redir == %s\n", redir[i].path_or_limiter);
		}
		else if (tmp->type == type2)// heredoc or dredir_out
		{
			redir[i].type = 2;// << or >> 
			redir[i].path_or_limiter = ft_strdup(tmp->content);
			printf("redir type %d\n", redir[i].type);
			printf("redir == %s\n", redir[i].path_or_limiter);
		}
		tmp = tmp->next;
		i++;
	}
	// printf("aaredir type %d\n", redir[0].type);
	// printf("aaaredir == %s\n", redir[0].path_or_limiter);
	// redir[i] = NULL;
	return (redir);
}

void	set_pipe_flag(t_simple_cmd *head, int cmd_nbr)
{
	if (cmd_nbr == 1)
		return;
	while (head)
	{
		if (head->i == 0)
			head->pipe_flag = 2; // after
		else if (head->i == cmd_nbr - 1)
			head->pipe_flag = 1; // before
		else
			head->pipe_flag = 3; // before and after
		head = head->next;
	}
}

