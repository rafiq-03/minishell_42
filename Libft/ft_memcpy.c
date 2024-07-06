/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 19:15:49 by rmarzouk          #+#    #+#             */
/*   Updated: 2023/12/29 12:42:45 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*pdst;
	unsigned char	*psrc;

	if (!src && !dst)
		return (NULL);
	if (src == dst)
		return (dst);
	pdst = (unsigned char *)dst;
	psrc = (unsigned char *)src;
	while (n--)
	{
		*pdst++ = *psrc++;
	}
	return (dst);
}
