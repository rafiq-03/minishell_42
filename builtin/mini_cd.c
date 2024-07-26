/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:31:37 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/26 16:00:25 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	mini_cd(t_env *env, char **cmd)
{
	char *current_dir;
    //if path_name == ".."
    //if path_name == "." we must doing anything
    // get current directory
    // check if the path_name of directory exists
    // if chdir returns 0 we must update the old_pwd and pwd in env and (mini_cd returnde 0)
    //else mini_cd retuned 1
    current_dir = getcwd(NULL, 0);
    if (current_dir)
		change_env_value(env, "OLDPWD" ,current_dir, 1);
    else
	{
        perror("Error");
		return (1);
	}
    if (chdir(cmd[1]) == -1)
    {
        perror("Error");
        return (1);
    }
    current_dir = getcwd(NULL, 0);
    if (current_dir)
		change_env_value(env, "PWD" ,current_dir, 1);
    else
    {
        perror("Error");
        return(1);
    }
    return(0);
    //every time its nessessory to set a success or faild value to an exit_status varible,
}
