/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors-utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:14:59 by mskhairi          #+#    #+#             */
/*   Updated: 2024/07/07 16:16:33 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int 	is_redirection(char *str)
{
	if (!ft_strncmp(str, ">>", 2) || !ft_strncmp(str, ">>", 2) || *(str) == '>' || *(str) == '<')
		return (1);
	return (0);
}

void check_redirections(t_item **lst)
{
	t_item *search;
	t_item *tmp;

	tmp = *lst;
	search = *lst;
	while (lst && tmp)
	{
		if (is_redirection(tmp->content))
		{
			while(search->prev)
			{
				if (!is_empty(search->prev->content) && !is_redirection(search->prev->content))
					break ;
				else
				{
					ft_free_list(lst);
					ft_print_error();
				}
				search = search->prev;
			}
		}
		tmp = tmp->next;
		search = tmp;
	}
}