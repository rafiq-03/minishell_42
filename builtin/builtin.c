/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:35:47 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/22 18:27:16 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	builtin_cmd(t_simple_cmd *buitin, t_data *data, int	flag)
{
	if (flag == 3)
		mini_env(data->env_l);
	(void)data;
	(void)buitin;
	printf("this is builtine function\n");
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
