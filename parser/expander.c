/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:27:32 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/13 15:01:29 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// expand values of env variables
// char *expander(char *env_var, t_env *env);

char *env_search(char *env_var)
{
	// implement later
	return (ft_strjoin("env", ft_strdup(env_var)));
}

void	expander(t_item	*list)
{
	char	*tmp;
	while (list)
	{
		if (list->type == ENV && list->state == IN_DQUOTE)
		{
			tmp = list->content;
			free(list->content);
			list->content = env_search(tmp + 1);
			list->type = WORD;
		}
		else if (list->type == ENV && list->state == IN_QUOTE)
			list->type = WORD;
		list = list->next;
	}
}