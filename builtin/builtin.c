/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:35:47 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/25 20:10:13 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	builtin_cmd(t_simple_cmd *builtin, t_data *data, int	flag)
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
		mini_cd();
	if (flag == 7)
		mini_exit();
	// printf("this is builtine function\n");
}

int	check_builtin(char *str)
{
	if (!ft_strncmp(str, "echo", ft_strlen(str)))
		return (1);
	if (!ft_strncmp(str, "pwd", ft_strlen(str)))
		return (2);
	if (!ft_strncmp(str, "env", ft_strlen(str)))
		return (3);
	if (!ft_strncmp(str, "unset", ft_strlen(str)))
		return (4);
	if (!ft_strncmp(str, "export", ft_strlen(str)))
		return (5);
	if (!ft_strncmp(str, "cd", ft_strlen(str)))
		return (6);
	if (!ft_strncmp(str, "exit", ft_strlen(str)))
		return (7);
	return (0);
}

void	change_env_value(t_env *env_l, char *key ,char *value)
{
	while (env_l)
	{
		if ((ft_strchr(key, '=') && !ft_strncmp(env_l->key, key, ft_strlen(key) - 1))
			|| !ft_strncmp(env_l->key, key, ft_strlen(key)))
		{
			if (!ft_strchr(env_l->key, '=') && ft_strchr(key, '='))
				env_l->key = ft_strjoin(env_l->key, ft_strdup("="));
			free(env_l->value);
			env_l->value = ft_strdup(value);
		}
		env_l = env_l->next;
	}
}

