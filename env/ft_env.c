/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:29:16 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/07 10:25:16 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "ft_env_utils.c"

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
	int		i;
	char	*key;
	char	*value;
	t_env	*tmp;

	i = -1;
	key = NULL;
	value = NULL;
	tmp = env_l;
	while (tmp)
	{
		printf("\033[0;32m%s\033[0m		=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
void	mini_unset(t_env **env_l , char *key);
void	ft_free(char **cmd)
{
	int i = 0;
	while (cmd[i])
	{
		free(cmd[i++]);	
	}
	free(cmd);
}

int main(int ac, char **av, char **env)
{
	t_env *env_l = env_list(env);
	char **cmd;
	char *input;
	while (1)
	{
		input = readline("prompt :");
		if (!ft_strncmp(input, "unset", ft_strlen("unset")))
		{
			cmd = ft_split(input, ' ');
			mini_unset(&env_l, cmd[1]);
			ft_free(cmd);
			
		}
		if (!ft_strncmp(input, "exit", 4))
		{
			free(input);
			system("leaks -q mini");
			exit(0);
		}
		if (!ft_strncmp(input, "env", 3))
			mini_env(env_l);
		add_history(input);
		free(input);
	}
}

void	mini_unset(t_env **env_l , char *key)
{
	t_env *tmp;
	
	tmp = *env_l;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(tmp->key)))
		{
			env_delone(env_l, tmp);
			return;
		}
		tmp = tmp->next;
	}
	printf("mal9ahch\n");
}
