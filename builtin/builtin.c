/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:35:47 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/31 12:24:46 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	handle_one_builtin(t_simple_cmd *builtin)
{
	// printf("in %d\n", builtin->fd.in);
	// printf("out %d\n", builtin->fd.out);
		dup2(STDIN_FILENO, builtin->fd.in);
		dup2(STDOUT_FILENO, builtin->fd.out);
	return (0);
}
void	builtin_cmd(t_simple_cmd *builtin, t_data *data, int	flag, bool one_cmd)
{
	
	if (one_cmd)
	{
		handle_one_builtin(builtin);
		// printf("one command\n");
	}
	else
		dup_and_close(builtin);
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
	if (one_cmd)
	{
		if (builtin->fd.in != 0)
			close(builtin->fd.in);
		if (builtin->fd.out != 1)
			close(builtin->fd.out);
	}
	if (!one_cmd)
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

