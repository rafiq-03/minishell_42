/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:33:23 by mskhairi          #+#    #+#             */
/*   Updated: 2024/07/21 19:00:39 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
    t_data  data;
    char    *prompt;
    while(1)
    {
        prompt = readline("[minishell]::~>");
		data.line = ft_strtrim(prompt, "\t \f\v\n\r");
		free(prompt);
        if (!ft_strlen(data.line) || is_empty(data.line))
            continue;
        if (ft_strlen(data.line))
        {
            add_history(data.line);
            if (handle_prompt(&data))
                continue;
        }
        clean_cmd(&data);
    }
}

int     handle_prompt(t_data *data)
{
	
    data->token_lst = lexer(data->line);
	free(data->line);
    if (!data->token_lst)
        return (1);
    data->new_lst = organizer(data->token_lst);
    if (!data->new_lst)
        return (1);
    data->limits_lst = set_cmd_limits(data->new_lst);
    // printf("-------------------------------------------\n");
    // system("leaks -q minishell");
    data->spl_cmd_lst = ft_cmd_list(data->limits_lst);
    // printf("-------------------------------------------\n");
    // system("leaks -q minishell");
    return (0);
}

