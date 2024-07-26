/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:25:36 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/26 12:07:56 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../lexer/lexer.h"
# include "../minishell.h"

void			set_tokens(t_item **head);

t_cmd_limits	*new_limit(t_item *start);
t_cmd_limits	*last_limit(t_cmd_limits *lst);
t_cmd_limits	*set_cmd_limits(t_item *head);
t_item			*skip_other_types(t_item *tmp);
void			expander(t_env *env_l, t_item *list);

// void	add_back_limit(t_cmd_limits **lst, t_cmd_limits *new);

int				cmd_number(t_cmd_limits *cmd);
char			**set_cmd_arr(t_cmd_limits *cmd);
int				check_redir(t_cmd_limits *cmd);
t_redir			*set_redirs(t_cmd_limits *cmd, int num);
void			set_pipe_flag(t_simple_cmd *head, int cmd_nbr);
void			add_back_simple_cmd(t_simple_cmd **lst, t_simple_cmd *new);
t_simple_cmd	*last_cmd(t_simple_cmd *lst);

// for testing
void			print_lst(t_cmd_limits *lst);
void			print(char **str);
void			print_cmd(t_simple_cmd *cmd);
void			print_cmds(t_simple_cmd *cmd);

// void			expander(t_item *list);

#endif
