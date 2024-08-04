/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:26:58 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/08/03 18:03:01 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../minishell.h"

int		mini_env(t_data *data);
bool	get_key_and_value(char *env, char **key, char **value);
int		mini_unset(t_env **env_l, char **cmd);
int		mini_export(t_simple_cmd *export, t_data *data);
int		mini_echo(char **cmd);
int		mini_pwd(void);
int		mini_cd(t_env *env, char **cmd);
int		mini_exit(char **cmd);
int		is_exist(t_data *data, char *key, char *value, bool value_flag);
void	change_env_value(t_env *env_l, char *key, char *value, bool value_flag);

t_env	*env_last(t_env *node);
t_env	*env_new_node(char *key, char *value);
void	env_add_back(t_env **head, t_env *new);
void	env_delone(t_env **head, t_env *node);
int		handle_here_doc(t_simple_cmd *cmd);
int		handle_redirections(t_simple_cmd *cmd);

#endif
