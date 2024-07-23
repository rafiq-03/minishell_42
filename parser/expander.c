/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:27:32 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/23 12:27:07 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	_check_before(t_item *list)
{
	if (list->prev)
		list = list->prev;
	while (list)
	{
		if (list->type != WHITE_SPACE)
			break ;
		list = list->prev;
	}
	if (list->type == HERE_DOC)
		return (1);
	return(0);
}

int	check_herdoc(t_item *list)
{
	if (list->prev)
		list = list->prev;
	while (list)
	{
		if ((list->type == WORD && list->state == GENERAL) || (list->type == HERE_DOC))
			break ;
		list = list->prev;
	}
	if (!list || (list->type == WORD && list->state == GENERAL && list->next->type == WHITE_SPACE))
		return (0);
	else if (list->type == HERE_DOC)
		return (1);
	else if (list->type == WORD && list->state == GENERAL && list->next->type != WHITE_SPACE)
		return(_check_before(list));
	return (0);
}

char	*env_search(char *env_var)
{
	// implement later
	(void)env_var;
	return (ft_strdup("env_var"));
}

void	expander(t_item *list)
{
	char	*tmp;

	while (list)
	{
		if (list->type == ENV)
		{
			if (!check_herdoc(list))
			{
				tmp = list->content;
				list->content = env_search(tmp + 1);
				// if (!list->content)
				// 	return ;//null check
				free(tmp);
			}
			list->type = WORD;
		}
		list = list->next;
	}
}
