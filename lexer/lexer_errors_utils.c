/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:14:59 by mskhairi          #+#    #+#             */
/*   Updated: 2024/07/09 10:36:40 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int 	is_redirection(char *str)
{
	if (!ft_strncmp(str, ">>", 2) || !ft_strncmp(str, ">>", 2) || *(str) == REDIR_OUT || *(str) == REDIR_IN)
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
