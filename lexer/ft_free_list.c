/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:26:17 by mskhairi          #+#    #+#             */
/*   Updated: 2024/07/06 17:57:57 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstdelone(t_item *lst)
{
	if (lst)
	{
		free(lst->content);
		free(lst);
	}
}

void	ft_free_list(t_item **lst)
{
	t_item	*current;
	t_item	*tmp;

	current = *lst;
	if (lst)
	{
		while (current)
		{
			tmp = current;
			current = current->next;
			ft_lstdelone(tmp);
		}
		*lst = NULL;
	}
}