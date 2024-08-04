/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:20:07 by mskhairi          #+#    #+#             */
/*   Updated: 2024/08/03 17:08:54 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*rtype(int type)
{
	char	*str;

	str = NULL;
	if (type == WORD)
		str = "WORD";
	else if (type == WHITE_SPACE)
		str = "WHITE_SPACES";
	else if (type == NEW_LINE)
		str = "NEW_LINE";
	else if (type == QOUTE)
		str = "QOUTE";
	else if (type == DOUBLE_QUOTE)
		str = "DOUBLE_QUOTE";
	else if (type == PIPE_LINE)
		str = "PIPE_LINE";
	else if (type == ENV)
		str = "ENV";
	else if (type == REDIR_IN)
		str = "REDIR_IN";
	else if (type == REDIR_OUT)
		str = "REDIR_OUT";
	else if (type == HERE_DOC)
		str = "HERE_DOC";
	else if (type == DREDIR_OUT)
		str = "DREDIR_OUT";
	else if (type == ESCAPE)
		str = "ESCAPE";
	else if (type == REDIR_IN_FILE)
		str = "REDIR_IN_FILE";
	else if (type == REDIR_OUT_FILE)
		str = "REDIR_OUT_FILE";
	else if (type == HERE_DOC_LIMITER)
		str = "HERE_DOC_LIMITER";
	else if (type == DREDIR_OUT_FILE)
		str = "DREDIR_OUT_FILE";
	return (str);
}

void	print_list(t_item *head)
{
	char	*token;
	char	*state[5] = {"general", "\033[0;32mIN_QUT\033[0m",
		"\033[0;33mIN_DQUT\033[0m", NULL};
	printf(" --------------------------------------------------------------------------------\n");
	printf("|	[CMD]	|	[len]	|	[state]	|	[token]				\n");
	printf(" --------------------------------------------------------------------------------\n");
	while (head)
	{
		token = rtype(head->type);
		printf("|	[%s]	|   %d		|	%s	|	%s			\n",
				head->content,
				head->len,
				state[head->state - 1],
				token);
		head = head->next;
	}
	printf(" _______________________________________________________________________________\n\n");
}
