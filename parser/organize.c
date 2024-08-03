/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:37:20 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/08/03 17:45:04 by mskhairi         ###   ########.fr       */
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

int	check_dol_join(t_item *list, int flag)
{
	if (!flag)
	{
		if (!ft_strcmp(list->content, "$") && list->state == GENERAL
			&& list->next && (list->next->type == DOUBLE_QUOTE
				|| list->next->type == QOUTE))
			return (0);
	}
	else if (flag)
	{
		if ((list && !(list->type == WHITE_SPACE && list->state == GENERAL)
				&& list->type != QOUTE && list->type != DOUBLE_QUOTE)
			|| (!ft_strcmp(list->content, "")))
			return (0);
	}
	return (1);
}

void	handle_list(t_item *list, t_item **new_list, int *type,
		char *join_content)
{
	while (list)
	{
		if (!check_dol_join(list, 0))
		{
			list = list->next;
			continue ;
		}
		if (!check_dol_join(list, 1))
			join_content = ft_strjoin(join_content, ft_strdup(list->content));
		if (((join_content) && ((!list->next) || (list->next
						&& (!join_limiter(list->next->type, list->next->state)
							|| !join_limiter(list->type, 0))))))
		{
			if (!join_limiter(list->type, 0))
				*type = list->type;
			add_back_items(new_list, new_item(join_content,
					ft_strlen(join_content), *type, GENERAL));
			free(join_content);
			join_content = NULL;
			*type = WORD;
		}
		list = list->next;
	}
}

// void	ft_new_list(t_item *list, t_item **new_list)
// {
// 	char	*join_content;
// 	int		type;

// 	join_content = NULL;
// 	type = WORD;
// 	handle_list(list, new_list, &type, join_content);
// }

// void	last_tokinization(t_item *list, int *flag)
void	last_tokinization(t_item *list)
{
	t_item	*tmp;

	tmp = list;
	// if (tmp)
	while (tmp)
	{
		if (tmp->type == REDIR_IN && tmp->next)
			tmp->next->type = REDIR_IN_FILE;
		else if (tmp->type == REDIR_OUT && tmp->next)
			tmp->next->type = REDIR_OUT_FILE;
		else if (tmp->type == DREDIR_OUT && tmp->next)
			tmp->next->type = DREDIR_OUT_FILE;
		else if (tmp->type == HERE_DOC && tmp->next)
			tmp->next->type = HERE_DOC_LIMITER;
		tmp = tmp->next;
	}
}

t_item	*organizer(t_env *env_l, t_item *list)
{
	t_item	*new_list;
	int		flag;
	char	*join_content;
	int		type;

	flag = 0;
	type = WORD;
	join_content = NULL;
	new_list = NULL;
	expander(env_l, list, NULL);
	handle_list(list, &new_list, &type, join_content);
	last_tokinization(new_list);
	if (flag)
		return (0);
	ft_clear_items(&list);
	return (new_list);
}
