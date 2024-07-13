/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:41:01 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/13 17:34:07 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	set these tokens
	REDIR_IN_FILE, // redir files
	HERE_DOC_LIMITER,
	REDIR_OUT_FILE, // redir files
	DREDIR_OUT_FILE,
*/

// if (tmp->type == PIPLINE && tmp->state != GENERAL)
//		tmp->state = WORD;

// void	set_tokens(t_itme *list);

void	change_token(t_item *list, int	type, int	token)
{
	if (list->type == type)
	{
		if (list->state == GENERAL)
			list->next->next->type = token;
		else
			list->type = WORD;
	}
}

void	set_tokens(t_item **head)
{
	t_item *list = *head;
	while (list)
	{
		if (list->type == REDIR_IN)
			change_token(list, REDIR_IN, REDIR_IN_FILE);
		if (list->type == REDIR_OUT)
			change_token(list, REDIR_OUT, REDIR_OUT_FILE);
		if (list->type == HERE_DOC)
			change_token(list, HERE_DOC, HERE_DOC_LIMITER);
		if (list->type == DREDIR_OUT)
			change_token(list, DREDIR_OUT, DREDIR_OUT_FILE);
		if (list->type == PIPE_LINE && list->state != GENERAL)
			list->type = WORD;
		list = list->next;
	}
}
