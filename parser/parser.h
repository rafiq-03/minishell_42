/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:25:36 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/13 16:23:43 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PARSER_H
# define PARSER_H

#include "../minishell.h"

//

void	set_tokens(t_item **head);




t_cmd_limits	*new_limit(t_item *start);
t_cmd_limits	*last_limit(t_cmd_limits *lst);
t_cmd_limits	*set_cmd_limits(t_item *head);
t_item			*skip_other_types(t_item *tmp);
// void	add_back_limit(t_cmd_limits **lst, t_cmd_limits *new);

int		cmd_number(t_cmd_limits *cmd);
char	**set_cmd_arr(t_cmd_limits *cmd);
int		check_redir(t_cmd_limits *cmd,  int	type_1, int	type_2);
t_redir	*set_redir(t_cmd_limits *cmd, int type1, int type2, int num);
void	set_pipe_flag(t_simple_cmd *head, int cmd_nbr);
void	add_back_simple_cmd(t_simple_cmd **lst, t_simple_cmd *new);
t_simple_cmd *last_cmd(t_simple_cmd *lst);

// for testing
void	print_lst(t_cmd_limits *lst);
void	print(char **str);
void	print_cmd(t_simple_cmd *cmd);
void	print_cmds(t_simple_cmd *cmd);

# endif

