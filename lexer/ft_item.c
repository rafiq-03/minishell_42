/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_item.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 06:57:29 by mskhairi          #+#    #+#             */
/*   Updated: 2024/07/07 16:17:10 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize(t_item *lst)
{
	t_item	*count;
	int		i;

	count = lst;
	i = 0;
	while (lst && count)
	{
		count = count->next;
		i++;
	}
	return (i);
}

t_item	*new_item(char *content, int len, enum e_token type, enum e_state state)
{
	t_item	*new_node;

	new_node = malloc(sizeof(t_item));
	if (!new_node)
	{
		printf("error substr\n");
		return (NULL);
	}
	new_node->content = ft_substr(content, 0, len);
	new_node->len = len;
	new_node->state = state;
	new_node->type = type;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

t_item	*last_item(t_item *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	add_back_items(t_item **lst, t_item *new)
{
	t_item	*last;

	if (lst && new)
	{
		if (*lst)
		{
			last = last_item(*lst);
			new->prev = last;
			last->next = new;
		}
		else
			*lst = new;
	}
}
