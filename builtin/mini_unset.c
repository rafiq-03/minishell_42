/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:31:25 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/08/03 17:53:47 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int	g_exit_status;

int	mini_unset(t_env **env_l, char **cmd)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = *env_l;
	while (cmd[++i])
	{
		while (tmp)
		{
			if (!ft_strncmp(tmp->key, cmd[i], ft_strlen(tmp->key)))
			{
				env_delone(env_l, tmp);
				return (EXIT_SUCCESS);
			}
			tmp = tmp->next;
		}
	}
	g_exit_status = EXIT_SUCCESS;
	// printf("mal9ahch\n");
	return (EXIT_SUCCESS);
}
