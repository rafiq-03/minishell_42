/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:28:17 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/08/04 15:59:56 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern int g_exit_status;
char **get_path_env(t_env *env_l)
{
	while (env_l)
	{
		if (!ft_strncmp(env_l->key, "PATH", 4))
			return (ft_split(env_l->value, ':'));
		env_l = env_l->next;
	}
	return (NULL);
}

char **list_to_arr(t_env *tmp)
{
	int i = 0;
	int	len = 0;
	char **env;
	t_env *env_l = tmp;
	while (tmp)
	{
		len++;
		tmp=tmp->next;
	}
	env = malloc (sizeof(char **) * (len + 1));
	i = 0;
	while (env_l && i < len)
	{
		if (env_l->value_falg)
		env[i++] = ft_strjoin(ft_strjoin(ft_strdup(env_l->key),
			ft_strdup("=")), ft_strdup(env_l->value));
		env_l = env_l->next;
	}
	env[i] = NULL;
	return (env);
}

char	*search_cmd_path(char **split_path, char *cmd_name, bool *flag)
{
	int i;

	char *cmd;
	char *tmp = ft_strjoin(ft_strdup("/"), ft_strdup(cmd_name));
	i = 0;
	while (split_path[i])
    {
        cmd = ft_strjoin(ft_strdup(split_path[i]), ft_strdup(tmp));
        if (!access(cmd, X_OK))
		{
			*flag = 1;
			return (cmd);
		}
		i++;
    }
	return (cmd_name);
}

int	is_valid(char *cmd_name)
{
	struct stat cmd_info;
	int	flag;

	flag = stat(cmd_name, &cmd_info);
	if (flag == -1)
		return (0);
	if (S_ISREG(cmd_info.st_mode) && (cmd_info.st_mode & S_IXUSR))
		return (1);
	return (0);
}

char *check_full_path(char *cmd, char **path)
{
	char *tmp;
	int i;

	i = 0;
	tmp = ft_strjoin(ft_strdup("/"), cmd);
	while (path && path[i])
	{
		cmd = ft_strjoin(ft_strdup(path[i]), ft_strdup(tmp));
		if (is_valid(cmd) == 1)
			return (cmd);
		i++;
	}
	if(is_valid(cmd))
		return (cmd);
	return (NULL);
}

char *cmd_exist(char *cmd, char *cmd_name,  char **path)
{
	bool	is_path;

	is_path = false;
	if (!path)
		return (NULL);
	if (cmd && !ft_strchr(cmd, '/'))
		return (check_full_path(cmd, path));
	else
	{
		is_path = true;
		if (is_valid(cmd) == 1)
			return (cmd);
	}
	handle_errors(cmd_name, is_path);
	return (NULL);
}
