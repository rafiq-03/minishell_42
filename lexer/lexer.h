/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 19:56:11 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/08/03 17:08:35 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../minishell.h"

t_item	*new_item(char *content, int len, enum e_token type,
			enum e_state state);
t_item	*last_item(t_item *lst);
int		ft_lstsize(t_item *lst);
int		is_empty(char *str);
int		is_whitespace(char c);
void	add_back_items(t_item **lst, t_item *new);
int		set_env_item(t_item **ptr2head, char *str, int i);
int		set_redout_item(t_item **ptr2head, char *str, int i);
int		set_redin_item(t_item **ptr2head, char *str, int i);
int		is_token(char c);
int		set_token_items(t_item **ptr2head, char *str, int i);
void	ft_add_state(t_item **head);
int		lexer_errors(t_item **lst);
void	ft_clear_items(t_item **lst);
int		is_empty(char *str);
int		is_redirection(int type);
void	ft_print_error(void);
int		check_redirections(t_item **lst);
int		check_pipes(t_item **lst, t_item	*tmp);
int		is_alone(t_item *lst);
void	reset_tokens(t_item *list);

// testing

void	print_list(t_item *head);
#endif
