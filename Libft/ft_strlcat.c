/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:29:26 by rmarzouk          #+#    #+#             */
/*   Updated: 2023/12/28 09:21:49 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	i;

	i = 0;
	dlen = ft_strlen(dst);
	if (dlen >= dstsize || dstsize == 0)
		return (dstsize + ft_strlen (src));
	while (*(src + i) && dlen + i < dstsize - 1)
	{
		dst[dlen + i] = src [i];
		i++;
	}
	dst[dlen + i] = '\0';
	return (dlen + ft_strlen (src));
}
