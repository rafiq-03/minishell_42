/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:33:23 by mskhairi          #+#    #+#             */
/*   Updated: 2024/08/04 14:54:11 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

void	handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 1;
	}
}

int	check_empty_input(char *prompt)
{
	if (!prompt) //is modefied!!
	{
		free(prompt);
		printf("exit\n");
		exit (g_exit_status);
	}
	else if (!*prompt)
	{
		free(prompt);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*tmp;

	(void)ac;
	(void)av;
	(void)env;
	g_exit_status = 0;
	data.env_l = env_list(env);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);//signal(SIGQUIT, SIG_DFL); in child proccesses
	while (1)
	{
		tmp = readline("minihell-3.2$ ");
		data.prompt = ft_strtrim(tmp, "\t \f\v\n\r");
		free(tmp);
		if (!check_empty_input(data.prompt))
			continue ;
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
	//check_builin(data->prompt); // check in command name for every command
	data->token_lst = lexer(data->prompt);
	free(data->prompt);
	if (!data->token_lst)
		return (1);
	data->new_lst = organizer(data->env_l, data->token_lst);
	if (!data->new_lst)
		return (1);
	data->limits_lst = set_cmd_limits(data->new_lst);
	data->spl_cmd_lst = ft_cmd_list(data->limits_lst, data);
	execute_cmd(data->spl_cmd_lst, data);
	return (0);
}
