/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:35:47 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/31 14:47:15 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	return_default_fd(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);
	return (0);
}

int execute_builtin(t_simple_cmd *builtin, t_data *data, int flag)
{
	if (flag == 1)
		mini_echo(builtin->cmd);
	if (flag == 2)
		mini_pwd();
	if (flag == 3)
		mini_env(data);
	if (flag == 4)
		mini_unset(&data->env_l, builtin->cmd);
	if (flag == 5)
		mini_export(builtin, data);
	if (flag == 6)
		mini_cd(data->env_l, builtin->cmd);
	if (flag == 7)
		mini_exit(builtin->cmd);
	return (0);
}

void	builtin_cmd(t_simple_cmd *builtin, t_data *data, int	flag, bool one_cmd)
{
	int in;
	int	out;
	
	if (one_cmd)
	{
		in = dup(STDIN_FILENO);
		out = dup(STDOUT_FILENO);
	}
	dup_and_close(builtin);
	execute_builtin(builtin, data, flag);
	if (one_cmd)
		return_default_fd(in, out);
	else
		exit(0);
}

int	check_builtin(char *str)
{
	if (!ft_strcmp(str, "echo"))
		return (1);
	if (!ft_strcmp(str, "pwd"))
		return (2);
	if (!ft_strcmp(str, "env"))
		return (3);
	if (!ft_strcmp(str, "unset"))
		return (4);
	if (!ft_strcmp(str, "export"))
		return (5);
	if (!ft_strcmp(str, "cd"))
		return (6);
	if (!ft_strcmp(str, "exit"))
		return (7);
	return (0);
}

void	change_env_value(t_env *env_l, char *key ,char *value, bool value_flag)
{
	while (env_l)
	{
		if (!ft_strncmp(env_l->key, key, ft_strlen(env_l->key)))
		{
			free(env_l->value);
			env_l->value = ft_strdup(value);
			env_l->value_falg = value_flag;
		}
		env_l = env_l->next;
	}
}

