/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleaner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:08:33 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/23 15:28:10 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// clean simple command ---------------------------------

void	ft_free_redir(t_redir *redir, int num)
{
	while (num--)
		free(redir[num].path_or_limiter);
	free(redir);
}

void	del_cmd_node(t_simple_cmd *lst)
{
	if (lst)
	{
		free(lst->cmd_name);
		ft_free(lst->cmd);
		ft_free_redir(lst->redirs, lst->redir_num);
		free(lst);
	}
}

void	ft_clear_cmd_lst(t_simple_cmd **lst)
{
	t_simple_cmd	*current;
	t_simple_cmd	*tmp;

	current = *lst;
	if (lst)
	{
		while (current)
		{
			tmp = current;
			current = current->next;
			del_cmd_node(tmp);
		}
		*lst = NULL;
	}
}
// clean command limits------------------------------
void	ft_clear_limits(t_cmd_limits **lst)
{
	t_cmd_limits	*current;
	t_cmd_limits	*tmp;

	current = *lst;
	if (lst)
	{
		while (current)
		{
			tmp = current;
			current = current->next;
			free(tmp);
		}
		*lst = NULL;
	}
}
