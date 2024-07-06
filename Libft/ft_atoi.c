/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:47:00 by rmarzouk          #+#    #+#             */
/*   Updated: 2023/12/28 11:46:05 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	long long int	res;
	int				sign;
	long long int	before;

	res = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		before = res;
		res = (res * 10) + (*str - 48);
		if (res / 10 != before && sign == -1)
			return (0);
		else if (res / 10 != before && sign == 1)
			return (-1);
		str++;
	}
	return (res * sign);
}
