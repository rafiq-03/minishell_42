/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:26:17 by mskhairi          #+#    #+#             */
/*   Updated: 2024/07/22 15:26:35 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	del_item(t_item *lst)
{
	if (lst)
	{
		free(lst->content);
		lst->content = NULL;
		free(lst);
		lst = NULL;
	}
}

void	ft_clear_items(t_item **lst)
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
			del_item(tmp);
		}
		*lst = NULL;
	}
}

void	clean_cmd(t_data *data)
{
	ft_clear_items(&data->new_lst); // free
	ft_clear_limits(&data->limits_lst); // todo
	ft_clear_cmd_lst(&data->spl_cmd_lst); // todo
}
