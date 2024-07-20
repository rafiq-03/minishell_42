/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:33:23 by mskhairi          #+#    #+#             */
/*   Updated: 2024/07/20 16:59:02 by mskhairi         ###   ########.fr       */
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
            mini.token_lst = organizer(mini.tokenization);
            // mini.limits = set_cmd_limits(mini.token_lst);
            // mini.cmds = ft_cmd_list(mini.limits);

			print_list(mini.tokenization);
            printf ("***********************************************\n");
			print_list(mini.token_lst);
            add_history(mini.line);
        }
    }
}
