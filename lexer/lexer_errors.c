/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:25:21 by mskhairi          #+#    #+#             */
/*   Updated: 2024/07/08 11:52:05 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_error(void)
{
	ft_putendl_fd("Syntax error", 2);
	exit(1);
} 



// void	check_quot_error(t_item **lst, char c)
// {
// 	t_item *tmp;
// 	// t_item *tmp1;
// 	int	count_quot;

// 	count_quot = 0;
// 	tmp = *lst;
// 	// tmp = *lst;
// 	// printf("hello\n");
// 	while(lst && tmp)
// 	{
// 		// // printf("size of list [%d]\n", ft_lstsize(*lst));
// 		// if (ft_lstsize(*lst) < 2)
// 		// {
// 		// 	if (*(tmp->content) == c)
// 		// 		count_quot++;
// 		// }
// 		// else
// 		// {
// 			if (*(tmp->content) == c)
// 			{
// 				if (!*(tmp->prev->content))
// 					count_quot++;
// 				else if (*(tmp->prev->content) != '\\')
// 					count_quot++;
// 			}
// 		tmp = tmp->next;
// 	}
// 	printf("==> %d\n", count_quot);
// 	if (count_quot % 2 != 0)
// 	{
// 		ft_free_list(lst);
// 		ft_print_error();
// 	}
// }

void check_pipes(t_item **lst)
{
	t_item *search;
	t_item *tmp;

	tmp = *lst;
	search = *lst;
	while (lst && tmp)
	{
		if (*(tmp->content) == '|')
		{
			while(search->prev)
			{
				if (!is_empty(search->prev->content) && !is_redirection(search->prev->content))
					break ;
				else if (is_redirection(search->prev->content))
				{
					ft_free_list(lst);
					ft_print_error();
				}
				search = search->prev;
			}
		}
		tmp = tmp->next;
		search = tmp;
	}
}

void	lexer_errors(t_item **lst)
{
	// check_quot_error(lst, '\'');
	// printf("---------------------------\n");
	// check_quot_error(lst, '\"');
	check_redirections(lst);
	// check_pipes(lst);
	// check_redout();
}
