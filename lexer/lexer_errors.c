/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:25:21 by mskhairi          #+#    #+#             */
/*   Updated: 2024/08/02 18:11:13 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_print_error(void)
{
	ft_putendl_fd("minihell: syntax error", 2);
}

int	check_quot(t_item *lst, char c)
{
	int	count_quote;

	count_quote = 0;
	while (lst)
	{
		if (lst->type == c && lst->state == GENERAL)
			count_quote++;
		lst = lst->next;
	}
	if (count_quote % 2 != 0)
		return (0);
	return (1);
}

int	check_quot_error(t_item *lst)
{
	if (!check_quot(lst, DOUBLE_QUOTE) || !check_quot(lst, QOUTE))
		return (0);
	return (1);
}

int	 lexer_errors(t_item **lst)
{
	if (!check_redirections(lst) || !check_pipes(lst)
		|| !check_quot_error(*lst))
	{
		ft_print_error();
		return (1); // there is an error;
	}
	return (0);
}
