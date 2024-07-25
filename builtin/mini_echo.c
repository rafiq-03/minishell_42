/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:30:56 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/25 13:08:35 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	mini_echo(char **str)
{
	int i;

	i = 1;
	if (str[i] && !ft_strncmp(str[i], "-n", ft_strlen(str[i])))
		i++;
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		if (str[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!str[1] || ft_strncmp(str[1], "-n", ft_strlen(str[1])))
		ft_putstr_fd("\n", 1);
	return (0);
}
