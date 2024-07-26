/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:31:02 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/26 11:18:36 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	print_env(t_env *env_l)
{
	while (env_l)
	{
		if (env_l->value_falg)
			printf("declare -x %s=\"%s\"\n", env_l->key, env_l->value);
		else
			printf("declate -x %s\n", env_l->key);
		env_l = env_l->next;
	}
}

int is_exist(t_data *data, char *key, char *value, bool value_flag)
{
	t_env	*tmp;

	tmp = data->env_l;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key)))
		{
			if (value_flag)
			{
				change_env_value(tmp, key, value, value_flag);
				tmp->value_falg = value_flag;
			}
			free(key);
			free(value);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
int	check_key(char *arg, bool *flag)// check if this key is valid
{
	int	i;

	i = 0;
	if (!arg)
		return (0);
	if(arg[i] != '_' && !ft_isalpha(arg[i]))
	{
		*flag = true;
		return (1);
	}
	while (arg[++i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_' && arg[i] != '=')
		{
			*flag = true;
			return (1);	
		}
	}
	return (0);
}

int	mini_export(t_simple_cmd *export, t_data *data)
{
	int	i;
	char	*key;
	char	*value;
	t_env	*new;
	bool	flag;
	bool	value_flag;

	flag = 0;
	i = 0;
	
	// system("leaks -q minishell");
	if (!export->cmd[1])
		print_env(data->env_l);
	while (export->cmd[++i])
	{
		value_flag = get_key_and_value(export->cmd[i], &key, &value);
		if (is_exist(data, key, value, value_flag))// pass false
			continue;
		if (check_key(key, &flag))// check bug of env without = " a= != a"
		{
			if (flag == 1)
			{
				ft_putstr_fd("export : `", 2);			
				ft_putstr_fd(export->cmd[i], 2);			
				ft_putstr_fd("\': not a valid identifier\n", 2);
			}
			continue;
		}
		// free(key);
		// free(value);
		new = env_new_node(key, value);
		new->value_falg = value_flag;
		env_add_back(&data->env_l, new);
	}
	// system("leaks -q minishell");
	return (0);
}
