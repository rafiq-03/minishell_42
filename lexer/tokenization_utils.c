/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 11:47:11 by mskhairi          #+#    #+#             */
/*   Updated: 2024/07/14 13:15:59 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	set_env_item(t_item **ptr2head, char *str, int i)
{
	if (is_token(str[i + 1]) || !str[i + 1])
		add_back_items(ptr2head, new_item(str, ++i, WORD, GENERAL));
	else if (str[++i] == '?' || (str[i] >= '0' && str[i] <= '9'))// check it later
		add_back_items(ptr2head, new_item(str, ++i, ENV, GENERAL));
	else
	{
		i++;
		while (str[i] && !is_token(str[i]))
			i++;
		add_back_items(ptr2head, new_item(str, i, ENV, GENERAL));
	}
	return (i);
}

int	set_redout_item(t_item **ptr2head, char *str, int i)
{
	if (str[i + 1] == REDIR_OUT)
	{
		i++;
		add_back_items(ptr2head, new_item(str, ++i, DREDIR_OUT, GENERAL));
	}
	else
		add_back_items(ptr2head, new_item(str, ++i, REDIR_OUT, GENERAL));
	return (i);
}

int	set_redin_item(t_item **ptr2head, char *str, int i)
{
	if (str[i + 1] == REDIR_IN)
	{
		i++;
		add_back_items(ptr2head, new_item(str, ++i, HERE_DOC, GENERAL));
	}
	else
		add_back_items(ptr2head, new_item(str, ++i, REDIR_IN, GENERAL));
	return (i);
}

int	set_token_items(t_item **ptr2head, char *str, int i)
{
	if (is_whitespace(str[i]))
		add_back_items(ptr2head, new_item(str, ++i, WHITE_SPACE, GENERAL));
	else if (str[i] == NEW_LINE)
		add_back_items(ptr2head, new_item(str, ++i, NEW_LINE, GENERAL));
	else if (str[i] == QOUTE)
		add_back_items(ptr2head, new_item(str, ++i, QOUTE, GENERAL));
	else if (str[i] == DOUBLE_QUOTE)
		add_back_items(ptr2head, new_item(str, ++i, DOUBLE_QUOTE, GENERAL));
	else if (str[i] == ESCAPE)
		add_back_items(ptr2head, new_item(str, ++i, ESCAPE, GENERAL));
	else if (str[i] == PIPE_LINE)
		add_back_items(ptr2head, new_item(str, ++i, PIPE_LINE, GENERAL));
	else if (str[i] == REDIR_IN)
		i += set_redin_item(ptr2head, str, i);
	else if (str[i] == REDIR_OUT)
		i += set_redout_item(ptr2head, str, i);
	else if (str[i] == ENV)
		i += set_env_item(ptr2head, str, i);
	return (i);
}
