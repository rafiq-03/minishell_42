/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:35:47 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/30 13:29:51 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	builtin_cmd(t_simple_cmd *builtin, t_data *data, int	flag)
{
	
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

