# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/06 14:50:47 by rmarzouk          #+#    #+#              #
#    Updated: 2024/07/23 16:07:34 by rmarzouk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror 
# CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
LIBS = -Llibft -lft -lreadline

LEXER_DIR=lexer/
S_LEXER= $(addprefix $(LEXER_DIR), 	\
									ft_lexer.c\
									ft_item.c\
									tokenization_utils.c \
									testing_print.c \
									ft_state.c \
									lexer_cleaner.c\
									lexer_errors.c\
									is_empty.c	\
									lexer_errors_utils.c	\
									reset_tokens.c\
									redirect_syntax.c)
O_LEXER=$(S_LEXER:.c=.o)

PARSER_DIR=parser/
S_PARSER= $(addprefix $(PARSER_DIR), 	\
										ft_cmd_limits.c\
										ft_command_utils.c\
										ft_command.c\
										organize.c\
										testing.c\
										expander.c\
										parser_cleaner.c\
									)
O_PARSER=$(S_PARSER:.c=.o)

BUILTIN_DIR=builtin/
S_BUILTIN= $(addprefix $(BUILTIN_DIR), 	\
										builtin.c\
										builtin_utils.c\
										mini_cd.c\
										mini_echo.c\
										mini_env.c\
										mini_export.c\
										mini_pwd.c\
										mini_unset.c\
										mini_exit.c\
									)
O_BUILTIN=$(S_BUILTIN:.c=.o)

EXECUTION_DIR=execution/
S_EXECUTION= $(addprefix $(EXECUTION_DIR), 	\
										execute_cmd.c\
									)
O_EXECUTION=$(S_EXECUTION:.c=.o)


NAME = minishell


all: $(NAME)

$(NAME): $(O_LEXER) $(O_PARSER) $(O_BUILTIN) $(O_EXECUTION) $(NAME).o
	make -C Libft
	$(CC) $(NAME).o $(CFLAGS) $(O_LEXER) $(O_PARSER) $(O_BUILTIN) $(O_EXECUTION) $(LIBS) -o $(NAME)

%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	make fclean -C Libft
	rm -f $(O_LEXER) $(NAME).o
	rm -rf $(O_PARSER)
	rm -rf $(O_BUILTIN)
	rm -rf $(O_EXECUTION)

fclean: clean
	rm -f $(NAME)

re: fclean all
