/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:31:25 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/26 11:27:30 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"


int	mini_unset(t_env **env_l , char **cmd)
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
				return (0);
			}
			tmp = tmp->next;
		}	
	}
	printf("mal9ahch\n");
	return (0);
}
