/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:30:56 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/08/03 17:59:21 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int	g_exit_status;

int	is_option(char **str, int *flag)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		if (!ft_strncmp(str[i], "-n", 2))
		{
			j = 2;
			while (str[i][j])
			{
				if (str[i][j] != 'n')
					return (i);
				j++;
			}
			*flag = 0;
		}
		else
			break ;
		i++;
	}
	return (i);
}

int	mini_echo(char **str)
{
	int	i;
	int	flag;

	flag = 1;
	i = is_option(str, &flag);
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		if (str[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!str[1] || flag)
		ft_putstr_fd("\n", 1);
	g_exit_status = EXIT_SUCCESS;
	return (EXIT_SUCCESS);
}
