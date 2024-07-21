/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:33:23 by mskhairi          #+#    #+#             */
/*   Updated: 2024/07/21 15:48:33 by rmarzouk         ###   ########.fr       */
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
        clean_cmd(&data, 1);
    }
}

int     handle_prompt(t_data *data)
{
    int flag;
    
    flag = 0;
    data->token_lst = lexer(data->line, &flag);
    if (flag == 1)
        return (clean_cmd(data, 1), 1);
    // data->new_lst = organizer(data->token_lst);
    // if (!data->new_lst)
    //     return (clean_cmd(data, 2), 1);
    // data->limits_lst = set_cmd_limits(data->new_lst);
    // if (!data->limits_lst)
    //     return (clean_cmd(data, 3), 1);
    // data->spl_cmd_lst = ft_cmd_list(data->limits_lst);
    // if (!data->spl_cmd_lst)
    //     return (clean_cmd(data, 4), 1);
    return (0);
}

