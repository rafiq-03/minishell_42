/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:26:58 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/25 16:49:28 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../minishell.h"

int		mini_env(t_data *data);
void	get_key_and_value(char *env, char **key, char **value);
int		mini_unset(t_env **env_l ,char **cmd);
// void	mini_export(t_env **env_l, char *key);
int		mini_export();
int		mini_echo(char **cmd);
int		mini_pwd();
int		mini_cd();
int		mini_exit();
int		is_exist(t_data *data, char *arg);

t_env	*env_last(t_env *node);
t_env	*env_new_node(char *key, char *value);
void	env_add_back(t_env **head, t_env *new);
void	env_delone(t_env **head, t_env *node);

#endif
