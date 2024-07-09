/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:13:09 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/09 10:39:18 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_lst(t_cmd_limits *lst)
{
	t_cmd_limits *tmp;
	t_item *tm;

	tmp = lst;
	while (tmp)
	{
		tm = tmp->start;
		printf("**************************************\n\n");
		while (tm != tmp->end)
		{
			printf("[%s]\t", tm->content);
			tm = tm->next;
		}
		printf("[%s]\t", tm->content);
		printf("\n");
		tmp = tmp->next;
	}
		printf("\n**************************************\n");
}

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
	{
		lst = lst->next;
	}
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
			// new->prev = last;
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

t_cmd_limits	*ft_parser(t_item **head)
{
	t_cmd_limits *list;
	t_cmd_limits *new;
	t_item	*tmp;

	tmp = *head;
	list = new_limit(tmp);
	tmp = skip_other_types(tmp);
	list->end = tmp;
	// printf("start  = %s\tend %s\n", list->start->content, list->end->content);
	while (tmp)
	{
		// printf("[%s]\n", tmp->content);
		if (tmp->type == PIPE_LINE && tmp->next)
		{
			// printf("pipe : %s\n", tmp->content);
			new = new_limit(tmp->next);
			tmp = skip_other_types(tmp);
			new->end = tmp;
			add_back_limit(&list, new);
		}
		tmp = tmp->next;
	}
	print_lst(list);
	return (list);
}

/*Test cases 
	|| ls segf
	|	not a good behaviour
	ls || ls segf
	
*/
