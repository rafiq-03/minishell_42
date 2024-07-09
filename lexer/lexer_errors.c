/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:25:21 by mskhairi          #+#    #+#             */
/*   Updated: 2024/07/09 13:01:11 by mskhairi         ###   ########.fr       */
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



void	lexer_errors(t_item **lst)
{
	// check_quot_error(lst, '\'');
	if (!check_redirections(lst) || !check_pipes(lst))
	{
		ft_free_list(lst);
		ft_print_error();
	}
}
