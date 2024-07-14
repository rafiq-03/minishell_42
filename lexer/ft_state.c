/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 10:54:25 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/14 13:15:31 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_item	*handle_quotes(t_item *tmp, int type, int state)
{
	if (tmp->next)
		tmp = tmp->next;
	while (tmp && tmp->type != type)
	{
		tmp->state = state;
		tmp = tmp->next;
	}
	return (tmp);
}

void	ft_add_state(t_item **head)// not perfect 
{
	/* we have a problem in the test "$PATH" it give state in_dquote to all*/
	t_item	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->type == QOUTE)
			tmp = handle_quotes(tmp, QOUTE, IN_QUOTE);
		else if (tmp->type == DOUBLE_QUOTE)
			tmp = handle_quotes(tmp, DOUBLE_QUOTE, IN_DQUOTE);
		else
			tmp->state = GENERAL;
		if (tmp)
			tmp = tmp->next;
	}
}
