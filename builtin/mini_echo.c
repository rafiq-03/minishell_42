/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:30:56 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/24 20:58:25 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"


int num_of_words(char **str)
{
	int i;
	int count;

	i = 1;
	count = 0;
	if (!str || !*str)
		return(0);
	while (str[i])
	{
		i++;
		count++;
	}
	return (count);
}

int	mini_echo(char **str)
{
	int i;
	i = 1;
	if (!str || !*str)
		return(0);
		printf("hello\n");
	printf("words [%d]\n", num_of_words(str));
	// while (str[i])
	// {
	// 	if (i == 2)
	// 	ft_putstr_fd(str[i], 1);
	// 	if (i != num_of_words(str) - 1)
	// 		ft_putstr_fd(" ", 1);
	// 	i++;
	// }
	// if (num_of_words(str) > 2 && !ft_strncmp(str[2], "-n", ft_strlen(str[2])))
	// 	ft_putstr_fd("\n", 1);
	return (0);
}
int main ()
{
	char *str = "eho -n hello";
	char **words = ft_split(str, ' ');
	mini_echo(words);
}
