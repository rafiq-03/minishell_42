/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:03:42 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/26 17:31:19 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include "../minishell.h"

char	**get_path_env(t_env *env_l);
char	*search_cmd_path(char **split_path, char *cmd_name, bool *flag);
char	**list_to_arr(t_env *tmp);



#endif
