/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:31:02 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/25 17:16:25 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// export buitin implmentation

int is_exist(t_data *data, char *arg)
{
	t_env	*tmp;

	tmp = data->env_l;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, arg, ft_strlen(arg)))
		{
			printf("deja kayn\n");
			env_delone(&data->env_l, tmp);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
int	check_key(char *arg, int *flag)
{
	int	i;

	i = 0;
	if (!arg)
		return (0);
	if(arg[i] != '_' && !ft_isalpha(arg[i]))
	{
		*flag = 1;
		return (1);
	}
	while (arg[++i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			*flag = 1;
			return (1);	
		}
	}
	return (0);
}

int	mini_export(t_simple_cmd *export, t_data *data)//t_simple_cmd *export, t_data *data)
{
	int	i;
	char	*key;
	char	*value;
	t_env	*new;
	int		flag;

	flag = 0;
	key = NULL;
	value = NULL;
	i = 0;
	
	while (export->cmd[++i])
	{
		get_key_and_value(export->cmd[i], &key, &value);
		if (check_key(key, &flag))
		{
			if (flag == 1)
				ft_putstr_fd("export : `", 2);			
				ft_putstr_fd(export->cmd[i], 2);			
				ft_putstr_fd("\': not a valid identifier\n", 2);			
			continue;
		}
		is_exist(data, key);
		new = env_new_node(key, value);
		env_add_back(&data->env_l, new);
	}
	return (0);
}
