/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:31:37 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/26 17:09:54 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int get_current_dir(t_env *env, char *pwd_type, char *current_dir)
{
	char *directory;

	directory = current_dir;
	if (!directory)
	{
		directory = getcwd(NULL, 0);
	}
    if (directory)
	{
		change_env_value(env, pwd_type ,directory, 1);
		free(directory);
	}
    else
	{
        perror("Error");
		return (1);
	}
	return (0);
}

int	mini_cd(t_env *env, char **cmd)
{
	char *current_dir;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		return (1);
	if (!cmd[1] || !ft_strncmp(cmd[1], "~", ft_strlen(cmd[1])))
	{
		if (chdir("/Users/mskhairi") == -1)
		{
			perror("Error");
			return (1);
		}
	}
    else if (chdir(cmd[1]) == -1)
    {
        perror("Error");
        return (1);
    }
	get_current_dir(env, "OLDPWD", current_dir);
	get_current_dir(env, "PWD", NULL);
    return(0);
}
