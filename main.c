/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:33:23 by mskhairi          #+#    #+#             */
/*   Updated: 2024/07/09 14:25:56 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
    char *input;
    t_item *lexer;
    while(1)
    {
        input = readline("[minishell]::~>");
        if (!input)
            printf("Exit\n");
        if (!ft_strncmp(input, "",ft_strlen(input)) || is_empty(input))
            return (1);
        if (ft_strlen(input))
        {
            lexer = my_lexer(input);
            ft_parser(&lexer);
            add_history(input);
        }
    }
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
