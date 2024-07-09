/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:19:03 by mskhairi          #+#    #+#             */
/*   Updated: 2024/07/08 15:20:44 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_whitespace(char c)
{
	if ((c == 32 || (c >= 9 && c <= 13)))
		return (1);
	return (0);
}

int	is_token(char c)
{
	if (is_whitespace(c) || c == '\n' || c == '\'' || c == '\"' || c == '\\'
		|| c == '$' || c == '|' || c == '<' || c == '>')
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

void	my_lexer(char *input)
{
	size_t	i;
	t_item	*head;

	head = NULL;
	i = 0;
	while (input[i] && i < ft_strlen(input))
		i += tokenization(&head, input + i);
	ft_add_state(&head);
	lexer_errors(&head);
	printf("----------\n");
	print_list(head);
}
