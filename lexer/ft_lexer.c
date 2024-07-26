/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:19:03 by mskhairi          #+#    #+#             */
/*   Updated: 2024/07/26 09:57:58 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_whitespace(char c)
{
	if ((c == 32 || (c >= 9 && c <= 13)))
		return (1);
	return (0);
}

int	is_token(char c)
{
	if (is_whitespace(c) || c == NEW_LINE || c == QOUTE || c == DOUBLE_QUOTE
		|| c == ESCAPE || c == ENV || c == PIPE_LINE || c == REDIR_IN
		|| c == REDIR_OUT)
		return (1);
	return (0);
}

int	tokenization(t_item **ptr2head, char *str)
{
	int	i;

	i = 0;
	if (is_token(str[i]))
	{
		i += set_token_items(ptr2head, str, i);
	}
	else
	{
		while (str[i] && !is_token(str[i]))
			i++;
		add_back_items(ptr2head, new_item(str, i, WORD, GENERAL));
	}
	return (i);
}

t_item	*lexer(char *input)
{
	size_t	i;
	t_item	*head;

	head = NULL;
	i = 0;
	while (input[i] && i < ft_strlen(input))
		i += tokenization(&head, input + i);
	ft_add_state(&head);
	reset_tokens(head);
	if (lexer_errors(&head))
		return (ft_clear_items(&head), NULL);
	// print_list(head);
	return (head);
}
