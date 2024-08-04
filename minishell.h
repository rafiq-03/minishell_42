/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:34:55 by mskhairi          #+#    #+#             */
/*   Updated: 2024/08/04 10:20:26 by rmarzouk         ###   ########.fr       */
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
# include <stdbool.h>
# include <fcntl.h>
#include <sys/stat.h>// stat system call
#include <errno.h> // error

/*---------------------------[ enum ]------------------------------*/

enum					e_token
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

enum					e_state
{
	GENERAL = 1,
	IN_QUOTE = 2,
	IN_DQUOTE = 3,
};

# define AFTER_PIPE 100
# define BEFORE_PIPE 101
# define BETWEEN_PIPES 102

/*------------------------[ typedefs ]----------------------------*/

// Lexing ----------------------//
typedef struct s_item
{
	char				*content; // must be freed
	int					len;
	enum e_token		type;
	enum e_state		state;
	struct s_item		*next;
	struct s_item		*prev;
}						t_item;

// Parsing :-------------------//

typedef struct s_cmd_limits
{
	t_item				*start;
	t_item				*end;
	int					i;
	struct s_cmd_limits	*next;
	// struct s_cmd_limits *prev;
}						t_cmd_limits;

// in_out_fd ::--------::
typedef struct s_fd
{
	int		in;// == 0
	int		out;// == 1
}						t_fd;

//redir ::-------------::

typedef struct s_redir
{
	int		type;
	char	*path_or_limiter;
	int		fd;// file descriptor of this redirection
		// path of this redir or limiter in the case of herdoc
}						t_redir;

// Simple command
typedef struct s_simple_cmd
{
	int					i;// index of command;
	char				*cmd_name;// command name
	char				**cmd;//command with its falags and options
	int					redir_num;// number of redir
	// we must check pipe flag befor assignment of in_out fd
	t_redir				*redirs;// redirs pointer
	t_fd				fd;//fd of in and out fd.in=open(redir_in->path);
	int					pipe[2];// pipe if needed
	int					pipe_flag;
	char				**heredoc_arr;
	int					heredoc_nbr;
	struct s_simple_cmd	*next;//next_command
	struct s_simple_cmd	*prev;// prev_command
	//10 elemnts
}						t_simple_cmd;

typedef struct s_env // this is for env variables
{
	char			*key;
	char			*value;
	bool			value_falg;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

//this struct will store all data
typedef struct s_data
{
	char			*prompt;// prompt
	t_item			*token_lst;//lexing
	t_item			*new_lst;// lexing
	t_cmd_limits	*limits_lst;// parsing
	t_simple_cmd	*spl_cmd_lst;//parsing
	t_env			*env_l;
	int				*fork_pid;// store data of forks;
	int				cmd_nbr;
}						t_data;

/*-------------------------Prototypes---------------------------------*/

/*-general prototypes------------------------*/

int						handle_prompt(t_data *data);
t_item					*lexer(char *input);
t_item					*organizer(t_env *env_l, t_item *list);
t_cmd_limits			*set_cmd_limits(t_item *head);
t_simple_cmd	*ft_cmd_list(t_cmd_limits *list, t_data *data);
int						is_empty(char *str);

int						execute_cmd(t_simple_cmd *cmd, t_data *data);
t_env					*env_list(char **env);//env list
void	builtin_cmd(t_simple_cmd *builtin, t_data *data, int flag, bool one_cmd);
int						check_builtin(char *str);


/*-cleaning prototypes------------------------*/

void					ft_clear_items(t_item **lst);
void					ft_clear_limits(t_cmd_limits **lst);
void					clean_cmd(t_data *data);
void					ft_clear_cmd_lst(t_simple_cmd **lst);

/*-execution prototypes-----------------------*/

int	dup_and_close(t_simple_cmd *cmd);
int	close_all_fds(t_simple_cmd *cmd);

// testing
void					print_list(t_item *head);
void					print(char **str);
void	print_cmds(t_simple_cmd *cmd);
void	print_cmd(t_simple_cmd *cmd);
int		mini_env(t_data *data);
int		is_whitespace(char c);
#endif

//if there is pipe or not : 0 -> no pipe  1 -> before 2 -> after 3 -> befor & after
