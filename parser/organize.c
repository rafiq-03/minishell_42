/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:37:20 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/20 17:58:27 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// create another linked list with expander values and removed of quotations

void	ft_new_list(t_item *list, t_item **new_list)
{
	char *join_content;
	int type;

	join_content = NULL;
	type = WORD;
	while (list)
	{
		if (list && (!(list->type == WHITE_SPACE && list->state == GENERAL)) && list->type != QOUTE && list->type != DOUBLE_QUOTE)
			join_content = ft_strjoin(join_content, list->content);
		if (!list->next || (list->next && join_content && (list->next->type == WHITE_SPACE && list->next->state == GENERAL)))
		{
			if (list->type == REDIR_IN || list->type == REDIR_OUT || list->type == DREDIR_OUT || list->type == HERE_DOC || list->type == PIPE_LINE)
				type = list->type;
			add_back_items(new_list, new_item(join_content, ft_strlen(join_content), type, GENERAL));
			free(join_content);
			join_content = NULL;
			type = WORD;
		}
		list = list->next;
	}
}

void	last_tokinization(t_item	*list)
{
	t_item *tmp;

	tmp = list;
	while (tmp)
	{	
		if (tmp->type == REDIR_IN)
				tmp->next->type = REDIR_IN_FILE;
		else if (tmp->type == REDIR_OUT)
				tmp->next->type = REDIR_OUT_FILE;
		else if (tmp->type == DREDIR_OUT)
				tmp->next->type = DREDIR_OUT_FILE;
		else if (tmp->type == HERE_DOC)
				tmp->next->type = HERE_DOC_LIMITER;
		tmp = tmp->next;
	}
}

t_item	*organizer(t_item *list)
{
	t_item	*new_list;

	new_list = NULL;
	expander(list);
	ft_new_list(list, &new_list);
	last_tokinization(new_list);
	return (new_list);
}
