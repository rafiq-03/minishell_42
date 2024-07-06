/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:50:30 by rmarzouk          #+#    #+#             */
/*   Updated: 2023/12/29 12:45:12 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;
	int		len;

	len = ft_strlen(s1);
	dst = (char *)malloc (len * sizeof(char) + 1);
	if (!dst)
		return (NULL);
	ft_memmove(dst, s1, len);
	dst[len] = '\0';
	return (dst);
}
