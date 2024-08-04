/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:59:01 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/08/03 17:58:04 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_env	*env_last(t_env *node) // get the last node of the env list
{
	if (!node)
		return (NULL);
	while (node->next != NULL)
		node = node->next;
	return (node);
}

t_env	*env_new_node(char *key, char *value) // add new node
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	env_add_back(t_env **head, t_env *new)
	//add a node to the last of env list
{
	t_env	*last;

	last = *head;
	if (head && new)
	{
		if (!*head)
			*head = new;
		else
		{
			last = env_last(*head);
			last->next = new;
			new->prev = last;
		}
	}
}

	// delete one node from the list >> here the problem :(
void	env_delone(t_env **head, t_env *node)
{
	if (node)
	{
		free(node->key);
		free(node->value);
		if (!node->prev) // first node
		{
			*head = node->next;
			node->next->prev = NULL;// last node
		}
		else if (!node->next)
			node->prev->next = NULL;
		else// other nodes
		{
			node->prev->next = node->next;
			node->next->prev = node->prev;
		}
	}
	free(node);
}
