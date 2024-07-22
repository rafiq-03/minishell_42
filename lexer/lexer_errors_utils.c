/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:14:59 by mskhairi          #+#    #+#             */
/*   Updated: 2024/07/22 15:28:16 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_redirection(int type)
{
	if (type == DREDIR_OUT || type == HERE_DOC || type == REDIR_OUT
		|| type == REDIR_IN)
		return (1);
	return (0);
}

int	check_pipes(t_item **lst)
{
	t_item	*search;
	t_item	*tmp;

	tmp = *lst;
	search = *lst;
	while (lst && tmp)
	{
		if (tmp->type == PIPE_LINE)
		{
			if (!is_alone(tmp))
				return (0);
			while (search->prev)
			{
				if (is_redirection(search->prev->type)
					|| search->prev->type == PIPE_LINE)
					return (0);
				else if (!is_empty(search->prev->content)
					&& !is_redirection(search->prev->type))
					break ;
				search = search->prev;
			}
		}
		tmp = tmp->next;
		search = tmp;
	}
	return (1);
}

int	check_redirections(t_item **lst)
{
	t_item	*search;
	t_item	*tmp;

	tmp = *lst;
	search = *lst;
	while (lst && tmp)
	{
		if (is_redirection(tmp->type))
		{
			if (!is_alone(tmp))
				return (0);
			while (search->prev)
			{
				if (is_redirection(search->prev->type))
					return (0);
				else if (!is_empty(search->prev->content)
					&& !is_redirection(search->prev->type))
					break ;
				search = search->prev;
			}
		}
		tmp = tmp->next;
		search = tmp;
	}
	return (1);
}
