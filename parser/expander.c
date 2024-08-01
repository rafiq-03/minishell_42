/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:27:32 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/08/01 09:43:57 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

extern int exit_status;
int	_check_before(t_item *list)
{
	if (list->prev)
		list = list->prev;
	while (list)
	{
		if (list->type != WHITE_SPACE)
			break ;
		list = list->prev;
	}
	if (list->type == HERE_DOC)
		return (1);
	return(0);
}

int	check_herdoc(t_item *list)
{
	if (list->prev)
		list = list->prev;
	while (list)
	{
		if ((list->type == WORD && list->state == GENERAL) || (list->type == HERE_DOC))
			break ;
		list = list->prev;
	}
	if (!list || (list->type == WORD && list->state == GENERAL && list->next->type == WHITE_SPACE))
		return (0);
	else if (list->type == HERE_DOC)
		return (1);
	else if (list->type == WORD && list->state == GENERAL && list->next->type != WHITE_SPACE)
		return(_check_before(list));
	return (0);
}

char	*env_search(t_env *env_l, char *env_var)
{
	t_env *tmp;
	
	tmp = env_l;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, env_var))// we must compare the values whit
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

void	expander(t_env *env_l, t_item *list)
{
	char	*tmp;
	int flag;

	flag = 0;
	while (list)
	{
		if (list->type == ENV)
		{
			if (!ft_strcmp(list->content, "$?"))
			{
				tmp = list->content;
				list->content = ft_itoa(exit_status);
				free(tmp);
				flag = 1;
			}
			if (!check_herdoc(list) && !flag)
			{
				tmp = list->content;
				list->content = env_search(env_l, tmp + 1);
				// if (!list->content)
				// 	exit_status = 126;
					// return ;//null check
				free(tmp);
			}
			list->type = WORD;
		}
		flag = 0;
		list = list->next;
	}
}
