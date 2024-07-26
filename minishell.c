/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:33:23 by mskhairi          #+#    #+#             */
/*   Updated: 2024/07/26 19:22:59 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*tmp;

	(void)ac;
	(void)av;
	(void)env;
	data.env_l = env_list(env);
	while (1)
	{
		// tmp = readline("\033[1;34m[minihell]::~> \033[0m");
		tmp = readline("[minihell]::~> ");
		data.prompt = ft_strtrim(tmp, "\t \f\v\n\r");
		free(tmp);
		if (!data.prompt || is_empty(data.prompt))//is modefied!!
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
    // check_builin(data->prompt); // check in command name for every command
	data->token_lst = lexer(data->prompt);
	free(data->prompt);
	if (!data->token_lst)
		return (1);
	data->new_lst = organizer(data->env_l, data->token_lst);
	if (!data->new_lst)
		return (1);
	data->limits_lst = set_cmd_limits(data->new_lst);
	data->spl_cmd_lst = ft_cmd_list(data->limits_lst);
	execute_cmd(data->spl_cmd_lst, data);
	return (0);
}
