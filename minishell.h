/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:34:55 by mskhairi          #+#    #+#             */
/*   Updated: 2024/07/08 12:07:52 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include "readline/readline.h"
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

enum				e_token
{
	WORD = -1,
	WHITE_SPACE,
	NEW_LINE = '\n',
	QOUTE = '\'',
	DOUBLE_QUOTE = '\"',
	ESCAPE = '\\',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	DREDIR_OUT,
};

enum				e_state
{
	GENERAL = 1,
	IN_QUOTE = 2,
	IN_DQUOTE = 3,
};

typedef struct s_item
{
	char			*content;
	int				len;
	enum e_token	type;
	enum e_state	state;
	struct s_item	*next;
	struct s_item	*prev;
}					t_item;

typedef	struct s_fd
{
	int	in; // == 0
	int	out; // == 1
}	t_fd;

//simple command
typedef struct s_simple_cmd
{
	char **cmd;//command with its falags and options
	char *redir_in; //name of in_file // NULL if there is no redir else there is redir
	char *redir_out; // name of ou_file // same
	t_fd fd; //file descriptor of in and out
	int	pipe[2];
	int	pipe_flag_before;// if there is a pipe or not
	int	pipe_flag_after;// if there is a pipe or not
	struct s_simple_cmd *next;
	struct s_simple_cmd *prev;
}	t_simple_cmd;

void		my_lexer(char *input);
t_item		*new_item(char *content, int len, enum e_token type, 
				enum e_state state);
t_item		*last_item(t_item *lst);

int	ft_lstsize(t_item *lst);

int			is_empty(char *str);
int			is_whitespace(char c);
void		add_back_items(t_item **lst, t_item *new);
int			set_env_item(t_item **ptr2head, char *str, int i);
int			set_redout_item(t_item **ptr2head, char *str, int i);
int			set_redin_item(t_item **ptr2head, char *str, int i);
int			is_token(char c);
int			set_token_items(t_item **ptr2head, char *str, int i);

void		ft_add_state(t_item **head);

void		print_list(t_item *head);

void	lexer_errors(t_item **lst);

void	ft_free_list(t_item **lst);

int is_empty(char *str);

int 	is_redirection(char *str);

void	ft_print_error(void);

void check_redirections(t_item **lst);



#endif
