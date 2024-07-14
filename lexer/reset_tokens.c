/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:01:21 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/14 13:15:52 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	exepted_tokens(t_item *list)
{
	if (list->type == WHITE_SPACE || list->type == WORD
		|| (list->type == ENV && list->state != IN_QUOTE))
		return (0);
	return (1);
}

void	reset_tokens(t_item *list)
{
	while (list)
	{
		if (exepted_tokens(list))
		{
			if (list->state != GENERAL)
				list->type = WORD;
		}
		list = list->next;
	}
}
