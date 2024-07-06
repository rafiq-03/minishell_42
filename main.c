/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:33:23 by mskhairi          #+#    #+#             */
/*   Updated: 2024/07/06 15:20:24 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_empty(char *str)
{
    int i = 0;

    while(str[i])
    {
        if (!(str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
            return(0);
        i++;
    }
    return(1);
}

int main()
{
    char *input;
    while(1)
    {
        input = readline("[minishell]::~>");
        if (!input)
            printf("Exit\n");
        if (!ft_strncmp(input, "",ft_strlen(input)) || is_empty(input))
            return (1);
        if (ft_strlen(input))
        {
            my_lexer(input);
            add_history(input);
        }
    }
}
