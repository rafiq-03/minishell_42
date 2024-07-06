/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:23:55 by rmarzouk          #+#    #+#             */
/*   Updated: 2023/12/29 10:55:53 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*pdst;
	unsigned char	*psrc;

	pdst = (unsigned char *)dst;
	psrc = (unsigned char *)src;
	if (!dst && !src)
		return (0);
	if (dst == src)
		return (dst);
	if (dst > src)
	{
		while (len--)
			*(pdst + len) = *(psrc + len);
	}
	else
	{
		while (len--)
			*pdst++ = *psrc++;
	}
	return (dst);
}
