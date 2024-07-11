# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/06 14:50:47 by rmarzouk          #+#    #+#              #
#    Updated: 2024/07/11 13:14:32 by rmarzouk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror 
LIBS = -Llibft -lft -lreadline

LEXER_DIR=lexer/
S_LEXER= $(addprefix $(LEXER_DIR), 	\
									ft_lexer.c\
									ft_item.c\
									tokenization_utils.c \
									testing_print.c \
									ft_state.c \
									ft_free_list.c	\
									lexer_errors.c\
									is_empty.c	\
									lexer_errors_utils.c	\
									redirect_syntax.c)
O_LEXER=$(S_LEXER:.c=.o)

PARSER_DIR=parser/
S_PARSER= $(addprefix $(PARSER_DIR), 	\
										ft_command_limits.c\
										ft_command_utils.c\
										ft_command.c\
										testing.c\
									)
O_PARSER=$(S_PARSER:.c=.o)


NAME = minishell


all: $(NAME)

$(NAME): $(O_LEXER) $(O_PARSER) main.o 
	make -C Libft
	$(CC) main.o $(CFLAGS) $(O_LEXER) $(O_PARSER) $(LIBS) -o $(NAME)

%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	make fclean -C Libft
	rm -f $(O_LEXER) main.o
	rm -r $(O_PARSER)

fclean: clean
	rm -f $(NAME)

re: fclean all
