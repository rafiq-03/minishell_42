/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:14:59 by mskhairi          #+#    #+#             */
/*   Updated: 2024/07/09 14:13:04 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redirection(char *str)
{
	if (!ft_strncmp(str, ">>", 2) || !ft_strncmp(str, ">>", 2) || *(str) == '>' || *(str) == '<')
		return (1);
	return (0);
}

int	check_pipes(t_item **lst)
{
	t_item	*search;
	t_item	*tmp;

	tmp = *lst;
	search = *lst;
	while (lst && tmp)
	{
		if (*(tmp->content) == '|')
		{
			while (search->prev)
			{
				if (!is_alone(tmp))
					return (0);
				if (is_redirection(search->prev->content) || *(search->prev->content) == '|')
					return (0);
				else if (!is_empty(search->prev->content)
						&& !is_redirection(search->prev->content))
					break ;
				search = search->prev;
			}
		}
		tmp = tmp->next;
		search = tmp;
	}
	return (1);
}


int	check_redirections(t_item	**lst)
{
	t_item	*search;
	t_item	*tmp;

	tmp = *lst;
	search = *lst;
	while (lst && tmp)
	{
		if (is_redirection(tmp->content))
		{
			if (!is_alone(tmp))
				return (0);
			while (search->prev)
			{
				if (is_redirection(search->prev->content))
					return(0);
				else if (!is_empty(search->prev->content)
						&& !is_redirection(search->prev->content))
					break ;
				search = search->prev;
			}
		}
		tmp = tmp->next;
		search = tmp;
	}
	return (1);
}
