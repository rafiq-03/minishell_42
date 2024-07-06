# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/06 14:50:47 by rmarzouk          #+#    #+#              #
#    Updated: 2024/07/06 15:22:48 by rmarzouk         ###   ########.fr        #
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
									ft_state.c)
O_LEXER=$(S_LEXER:.c=.o)


NAME = minishell


all: $(NAME)

$(NAME): $(O_LEXER) main.o
	make -C Libft
	$(CC) main.o $(CFLAGS) $(O_LEXER) $(LIBS) -o $(NAME)

%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	make fclean -C Libft
	rm -f $(O_LEXER) main.o

fclean: clean
	rm -f $(O_LEXER) $(NAME)

re: fclean all
