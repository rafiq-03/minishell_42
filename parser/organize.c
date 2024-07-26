/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:37:20 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/26 12:06:31 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// create another linked list with expander values and removed of quotations

int	join_limiter(int type, int state)
{
	if (((type == WHITE_SPACE && state == GENERAL) || type == REDIR_IN
			|| type == REDIR_OUT || type == DREDIR_OUT || type == HERE_DOC
			|| type == PIPE_LINE) && type != QOUTE && type != DOUBLE_QUOTE)
		return (0);
	return (1);
}

void	ft_new_list(t_item *list, t_item **new_list)
{
	char	*join_content;
	int		type;

	join_content = NULL;
	type = WORD;
	while (list)
	{
		if (list && (!(list->type == WHITE_SPACE && list->state == GENERAL))
			&& list->type != QOUTE && list->type != DOUBLE_QUOTE)
			join_content = ft_strjoin(join_content, ft_strdup(list->content));
		if ((join_content && *join_content) && ((!list->next) || (list->next
					&& (!join_limiter(list->next->type, list->next->state)
						|| !join_limiter(list->type, 0)))))
		{
			if (!join_limiter(list->type, 0))
				type = list->type;
			add_back_items(new_list, new_item(join_content,
					ft_strlen(join_content), type, GENERAL)); //new item
			free(join_content); //ft_free();
			join_content = ft_strdup(""); //ft_free();
			type = WORD;
		}
		list = list->next;
	}
	free(join_content); //ft_free();
}

void	last_tokinization(t_item *list)
{
	t_item	*tmp;

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

t_item	*organizer(t_env *env_l, t_item *list)
{
	t_item	*new_list;

	new_list = NULL;
	expander(env_l, list);
	ft_new_list(list, &new_list);
	last_tokinization(new_list);
	ft_clear_items(&list);
	// print_list(new_list);
	return (new_list);
}
