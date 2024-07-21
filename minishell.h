/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:34:55 by mskhairi          #+#    #+#             */
/*   Updated: 2024/07/21 16:32:27 by mskhairi         ###   ########.fr       */
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
	REDIR_IN_FILE, // redir files
	HERE_DOC_LIMITER,
	REDIR_OUT_FILE, // redir files
	DREDIR_OUT_FILE,
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
	char			*content;// must be freed
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
	int	type;// out [ (1 = '>') (2 = '>>') ] //  in [ (1 = '<') (2 = '<<') ]
	char *path_or_limiter;// path of this redir or limiter in the case of herdoc
}	t_redir;

// Simple command
typedef struct s_simple_cmd
{
	int	i;// index of command;
	char *cmd_name;// command name
	char **cmd;//command with its falags and options
	int	in_num;// number of redir
	int	out_num;// number of redir out
	// we must check pipe flag befor assignment of in_out fd
	t_redir	*redir_in;//in 
	t_redir	*redir_out;//out
	t_fd fd; //file descriptor of in and out ft.in = open(redir_in->path);
	int	pipe[2];// pipe if needed
	int	pipe_flag;// if there is a pipe or not : 0 = no pipe  1 = before 2 = after 3 = befor & after
	struct s_simple_cmd *next;//next_command
	struct s_simple_cmd *prev;// prev_command
	//10 elemnts
	
}	t_simple_cmd;

//this struct will store all data
typedef struct s_data
{
	char			*line;// line
	t_item			*token_lst;//lexing
	t_item			*new_lst; // lexing
	t_cmd_limits	*limits_lst; // parsing
	t_simple_cmd	*spl_cmd_lst; //parsing
}	t_data;

/*-------------------------Prototypes---------------------------------*/

/*-general prototypes------------------------*/

int				handle_prompt(t_data *data);
t_item			*lexer(char *input);
t_item			*organizer(t_item *list);
t_cmd_limits	*set_cmd_limits(t_item *head);
t_simple_cmd	*ft_cmd_list(t_cmd_limits *list);
int				is_empty(char *str);

/*-cleaning prototypes------------------------*/

void			ft_clear_items(t_item **lst);
void			ft_clear_limits(t_cmd_limits **lst);
void			clean_cmd(t_data *data);
void			ft_clear_cmd_lst(t_simple_cmd **lst);

// testing
void			print_list(t_item *head);
#endif
