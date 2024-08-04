/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:31:37 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/08/04 14:52:13 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int	g_exit_status;

int	get_current_dir(t_env *env, char *pwd_type, char *current_dir)
{
	char	*directory;

	directory = current_dir;
	if (!directory)
	{
		directory = getcwd(NULL, 0);
	}
	if (directory)
	{
		change_env_value(env, pwd_type, directory, 1);
		free(directory);
	}
	else
	{
		perror("minishell");
		g_exit_status = EXIT_FAILURE;
		return (1);
	}
	return (0);
}

int	get_home_env(t_env *env_l)
{
	char	*home_env;

	while (env_l)
	{
		if (!strcmp(env_l->key, "HOME"))
		{
			home_env = ft_strdup(env_l->value);
			if (chdir(home_env) == -1)
			{
				free(home_env);
				perror("minishell");
				g_exit_status = EXIT_FAILURE;
				return (1);
			}
			free(home_env);
		}
		env_l = env_l->next;
	}
	return (0);
}

int	mini_cd(t_env *env, char **cmd)
{
	char	*current_dir;
	

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		return (1);
	if (!cmd[1] || !ft_strcmp(cmd[1], "~"))
		get_home_env(env);
	else if (chdir(cmd[1]) == -1)
	{
		perror("minishell");
		g_exit_status = EXIT_FAILURE;
		return (1);
	}
	get_current_dir(env, "OLDPWD", current_dir);
	get_current_dir(env, "PWD", NULL);
	g_exit_status = EXIT_SUCCESS;
	return (0);
}
