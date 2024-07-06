/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 10:54:25 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/06 15:09:37 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_quotes(t_item *tmp, int *last_state, int *last, int state)
{
	if (last_state[*last] == state) // if the state is in quote it's mean it is last quote
		tmp->state = last_state[--(*last)];
	else
	{
		last_state[++(*last)] = state;
		tmp->state = last_state[*last - 1];
	}
}

void	ft_add_state(t_item **head)
{
	int	last_state[1024];
	int	last;
	t_item	*tmp;

	tmp = *head;
	last_state[0] = GENERAL;
	last = 0;
	while (tmp)
	{
		if (tmp->type == QOUTE)
			handle_quotes(tmp, last_state, &last, IN_QUOTE);
		else if (tmp->type == DOUBLE_QUOTE)
			handle_quotes(tmp, last_state, &last, IN_DQUOTE);
		else
			tmp->state = last_state[last];
		tmp = tmp->next;
	}
}

	// int a = -1;
	// printf("\n");
	// while (++a < 6)
	// {
	// 	printf("| %d ", last_state[a]);
	// }
	// printf("|\n\n");
