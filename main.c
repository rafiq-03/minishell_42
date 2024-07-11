/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:33:23 by mskhairi          #+#    #+#             */
/*   Updated: 2024/07/11 15:04:56 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
    t_data  mini;

    char *tmp;

    while(1)
    {
        tmp = readline("[minishell]::~>");
		mini.line = ft_strtrim(tmp, "\t \f\v\n\r");
		free(tmp);
        if (!mini.line)
            printf("Exit\n");
        if (!ft_strncmp(mini.line, "",ft_strlen(mini.line)) || is_empty(mini.line))
            return (1);
        if (ft_strlen(mini.line))
        {
            mini.tokenization = my_lexer(mini.line);
            mini.limits = set_cmd_limits(mini.tokenization);
            add_history(mini.line);
        }
    }
}
