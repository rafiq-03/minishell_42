/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_limits.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:13:09 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/11 13:15:08 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd_limits	*new_limit(t_item *start)
{
	t_cmd_limits *new;

	new = malloc(sizeof(t_cmd_limits));
	if (!new)
		return (NULL);
	new->i = 0;
	new->start = start;
	new->end = NULL;
	new->next = NULL;
	return (new);
}

t_cmd_limits	*last_limit(t_cmd_limits *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_back_limit(t_cmd_limits **lst, t_cmd_limits *new)
{
	t_cmd_limits	*last;

	if (lst && new)
	{
		if (*lst)
		{
			last = last_limit(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

t_item	*skip_other_types(t_item *tmp)
{
	if (tmp->next && tmp->next->type != PIPE_LINE)
		tmp = tmp->next;
	while (tmp && tmp->next && tmp->next->type != PIPE_LINE)
		tmp = tmp->next;
	return (tmp);
}

t_cmd_limits	*set_cmd_limits(t_item *head)
{
	t_cmd_limits *list;
	t_cmd_limits *new;
	int			i;

	i = 0;
	list = new_limit(head);
	head = skip_other_types(head);
	list->end = head;
	// printf("start  = %s\tend %s\n", list->start->content, list->end->content);
	while (head)
	{
		// printf("[%s]\n", tmp->content);
		if (head->type == PIPE_LINE && head->state == GENERAL && head->next)
		{
			// printf("pipe : %s\n", tmp->content);
			new = new_limit(head->next);
			head = skip_other_types(head);
			new->end = head;
			new->i = ++i;
			add_back_limit(&list, new);
		}
		head = head->next;
	}
	print_lst(list);
	return (list);
}

/*Test cases 
	|| ls segf
	|	not a good behaviour
	ls || ls segf
	
*/
