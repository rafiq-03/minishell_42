/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:33:23 by mskhairi          #+#    #+#             */
/*   Updated: 2024/07/09 15:25:47 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
    char *input;
    char *tmp;
    t_item *lexer;

    while(1)
    {
        tmp = readline("[minishell]::~>");
		input = ft_strtrim(tmp, "\t \f\v\n\r");
		free(tmp);
		//ft_strtrim() for delete the space 
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
}