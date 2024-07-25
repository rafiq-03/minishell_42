/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:26:58 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/25 18:15:09 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../minishell.h"

int		mini_env(t_data *data);
int		get_key_and_value(char *env, char **key, char **value);
int		mini_unset(t_env **env_l ,char **cmd);
int		mini_export(t_simple_cmd *export, t_data *data);
int		mini_echo(char **cmd);
int		mini_pwd();
int		mini_cd();
int		mini_exit();
int		is_exist(t_data *data, char *key, char *value);
void	change_env_value(t_env *env_l, char *key, char *value);

t_env	*env_last(t_env *node);
t_env	*env_new_node(char *key, char *value);
void	env_add_back(t_env **head, t_env *new);
void	env_delone(t_env **head, t_env *node);

#endif
