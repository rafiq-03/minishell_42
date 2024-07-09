/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:40:06 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/09 12:56:48 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_simple_cmd *new_cmd_node(t_cmd_limits *cmd)
{
	t_simple_cmd *new;

	new = malloc(sizeof(t_simple_cmd));
	if(!new)
		return (NULL);
	// fille with cmd_name
	new->next = NULL;
	new->prev = NULL;
	new->pipe_flag_after = 0;
	new->pipe_flag_before = 0;
	new->fd.in = -1;
	new->fd.out = -1;
	new->redir_in = NULL;
	new->redir_out = NULL;
	
	return (new);
}




// t_simple_cmd	*ft_fill_cmd(t_cmd_limits **list)
// {
// 	t_simple_cmd *cmds_list;
// 	t_simple_cmd *new_cmd;

// 	cmds_list = new_cmd_node(); //create a node;
// 	/*
// 		implement :
// 			* cmd name and its options and flags
// 			* redir if there is
// 			* pipe if needed
// 	*/
	
// }
