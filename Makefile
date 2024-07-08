# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/06 14:50:47 by rmarzouk          #+#    #+#              #
#    Updated: 2024/07/07 16:24:59 by mskhairi         ###   ########.fr        #
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
									lexer_errors_utils.c)
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
