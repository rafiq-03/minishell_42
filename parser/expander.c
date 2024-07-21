/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:27:32 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/21 16:06:22 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// expand values of env variables
// char *expander(char *env_var, t_env *env);

int	check_herdoc(t_item *list)
{
	if (list->prev)
		list = list->prev;
	while(list)
	{
		if (list->type != WHITE_SPACE)
			break;
		list = list->prev;
	}
	if (list->type == HERE_DOC)
		return (1);
	return (0);
}

char	*env_search(char *env_var)
{
	// implement later
	printf("%s\n", env_var);
	return (ft_strjoin(ft_strdup("env-"), env_var));
}

void	expander(t_item *list)
{
	char	*tmp;

	while (list)
	{
		if (list->type == ENV)
		{
			if (!check_herdoc(list))
			{
				tmp = list->content;
				list->content = env_search(tmp + 1);
				// if (!list->content)
				// 	return ;//null check
				free(tmp);
			}
			list->type = WORD;
		}
		list = list->next;
	}
}
