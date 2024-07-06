/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_item.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 06:57:29 by mskhairi          #+#    #+#             */
/*   Updated: 2024/07/06 15:09:33 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			last->next = new;
		}
		else
			*lst = new;
	}
}
