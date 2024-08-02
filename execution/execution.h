/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:03:42 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/08/02 11:35:00 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include "../minishell.h"

char	**get_path_env(t_env *env_l);
char	*search_cmd_path(char **split_path, char *cmd_name, bool *flag);
char	**list_to_arr(t_env *tmp);
char	*cmd_exist(char *cmd_name, char **path, bool *exist);

int	handle_pipes(t_simple_cmd *cmd);
int handle_here_doc(t_simple_cmd *cmd);
int handle_redirections(t_simple_cmd *cmd);
int	last_redir(t_redir *redir, int len, int type, int last_fd);
int	close_all_fds(t_simple_cmd *cmd);
void handle_errors(const char *cmd, int flag);

#endif
