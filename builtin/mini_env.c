/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:29:16 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/22 18:28:43 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	get_key_and_value(char *env, char **key, char **value)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	*key = ft_substr(env, 0, i);
	*value = ft_strdup(env + i + 1);
}

t_env	*env_list(char **env)//make new env list based on the the parent bash env
{
	t_env	*head;
	t_env	*tmp;
	char	*key;
	char	*value;
	int		i;

	get_key_and_value(env[0], &key, &value);
	head = env_new_node(key, value);
	i = 0;
	while (env[++i])
	{
		get_key_and_value(env[i], &key, &value);
		tmp = env_new_node(key, value);
		env_add_back(&head, tmp);
	}
	return (head);
}

void	mini_env(t_env *env_l)// implement env command
{
	while (env_l)
	{
		printf("%s=%s\n", env_l->key, env_l->value);
		env_l = env_l->next;
	}
}
