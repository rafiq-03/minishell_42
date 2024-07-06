/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:37:16 by rmarzouk          #+#    #+#             */
/*   Updated: 2023/12/26 13:58:00 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	number_len(int n)
{
	size_t			i;

	i = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*dst;
	size_t		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = number_len(n);
	dst = malloc ((len + 1) * sizeof(char));
	if (!dst)
		return (0);
	dst[len] = '\0';
	if (n == 0)
		dst[0] = 48;
	if (n < 0)
	{
		dst[0] = '-';
		n *= -1;
	}
	while (len-- && n > 0)
	{
		dst[len] = (n % 10) + 48;
		n /= 10;
	}
	return (dst);
}
