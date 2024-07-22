/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:33:23 by mskhairi          #+#    #+#             */
/*   Updated: 2024/07/22 16:15:19 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_data	data;
	char	*tmp;

	while (1)
	{
		tmp = readline("\033[1;34m[minihell]::~> \033[0m");
		data.prompt = ft_strtrim(tmp, "\t \f\v\n\r");
		free(tmp);
		if (!ft_strlen(data.prompt) || is_empty(data.prompt))
		{
			free(data.prompt);
			continue ;
		}
		if (ft_strlen(data.prompt))
		{
			add_history(data.prompt);
			if (handle_prompt(&data))
				continue ;
		}
		clean_cmd(&data);
	}
}

int	handle_prompt(t_data *data)
{
    // check_builin(data->prompt);
	data->token_lst = lexer(data->prompt);
	free(data->prompt);
	if (!data->token_lst)
		return (1);
	data->new_lst = organizer(data->token_lst);
	if (!data->new_lst)
		return (1);
	data->limits_lst = set_cmd_limits(data->new_lst);
	data->spl_cmd_lst = ft_cmd_list(data->limits_lst);
	return (0);
}
