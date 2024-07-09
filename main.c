/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:33:23 by mskhairi          #+#    #+#             */
/*   Updated: 2024/07/09 10:56:59 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("[minishell]::~>");
		//str_trim
		if (!input)
			printf("Exit\n");
		if (!ft_strncmp(input, "", ft_strlen(input)) || is_empty(input))
			return (1);
		if (ft_strlen(input))
		{
			my_lexer(input);
			add_history(input);
		}
	}
}
