/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:34:55 by mskhairi          #+#    #+#             */
/*   Updated: 2024/07/09 12:55:58 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*------------------------[ includes ]----------------------------------*/

# include "Libft/libft.h"
# include "readline/readline.h"
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/*---------------------------[ enum ]------------------------------------*/

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

/*-------------------------------------[ typedefs ]--------------------------------------*/

// Lexing ----------------------//
typedef struct s_item
{
	char			*content;
	int				len;
	enum e_token	type;
	enum e_state	state;
	struct s_item	*next;
	struct s_item	*prev;
}					t_item;

// Parsing :-------------------//


typedef struct s_cmd_limits
{
	t_item *start;
	t_item *end;
	int		i;
	struct s_cmd_limits *next;
	// struct s_cmd_limits *prev;
}	t_cmd_limits;

// in_out_fd ::--------::
typedef	struct s_fd
{
	int	in; // == 0
	int	out; // == 1
}	t_fd;

//redir ::-------------::

typedef	struct	s_redir
{
	int	num;// number of this redir type
	int	type;// out [ (1 = '>') (2 = '>>') ] //  in [ (1 = '<') (2 = '<<') ]         
	char *path;// path of this redir
}	t_redir;

// Simple command
typedef struct s_simple_cmd
{
	char *cmd_name;
	char **cmd;//command with its falags and options
	t_redir	*redir_in;//in
	t_redir	*redir_out;//out
	t_fd fd; //file descriptor of in and out
	int	pipe[2];// pipe if needed
	int	pipe_flag_before;// if there is a pipe or not
	int	pipe_flag_after;// if there is a pipe or not
	struct s_simple_cmd *next;
	struct s_simple_cmd *prev;
}	t_simple_cmd;

//this struct will store all data
typedef struct s_data
{
	t_simple_cmd	*cmds;
	t_item			*tokenization;
	t_cmd_limits	*limits;
}	t_data;

/*-------------------------Prototypes---------------------------------*/


t_item		*my_lexer(char *input);
t_item		*new_item(char *content, int len, enum e_token type, enum e_state state);
t_item		*last_item(t_item *lst);

int			ft_lstsize(t_item *lst);

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

void			lexer_errors(t_item **lst);

void			ft_free_list(t_item **lst);

int 			is_empty(char *str);

int 			is_redirection(char *str);
t_cmd_limits	*ft_parser(t_item **head);

void			ft_print_error(void);

void 			check_redirections(t_item **lst);



#endif
