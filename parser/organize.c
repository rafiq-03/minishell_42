/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:37:20 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/20 11:56:41 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// create another linked list with expander values and removed of quotations

void	ft_new_list(t_item *list, t_item **new_list)
{
	while (list)
	{
		if (!is_empty(list->content) && !(list->type == DOUBLE_QUOTE || list->type == QOUTE))
		{
			if(list->type == WORD)
				add_back_items(new_list, new_item(list->content, ft_strlen(list->content), list->type, list->state));
		}
		list = list->next;
	}
}

t_item	*organizer(t_item *list)
{
	t_item	*new_list;

	new_list = NULL;
	expander(list);
	ft_new_list(list, &new_list);
	// set tokens
	return (new_list);
}
