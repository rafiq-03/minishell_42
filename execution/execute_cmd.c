/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:05:09 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/25 17:22:00 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	_execute(t_simple_cmd *cmd, t_data *data)
{
	(void)data;
	printf("execute command : %s\n", cmd->cmd_name);
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

