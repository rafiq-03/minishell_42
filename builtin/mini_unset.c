/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:31:25 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/23 13:14:09 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"


int	mini_unset(t_env **env_l , char *key)
{
	t_env *tmp;
	
	tmp = *env_l;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(tmp->key)))
		{
			env_delone(env_l, tmp);
			return (0);
		}
		tmp = tmp->next;
	}
	printf("mal9ahch\n");
	return (0);
}
