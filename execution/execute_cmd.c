/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:05:09 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/22 17:15:49 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_cmd(t_simple_cmd *cmd)
{
	while (cmd)
	{
		if (check_buitin(cmd->cmd_name))
			buitin_cmd(cmd);
		else
			_execute(cmd);
		cmd = cmd->next;
	}
}

int	_execute(t_simple_cmd *cmd)
{
	printf("execute command %s\n", cmd->cmd_name);
}
