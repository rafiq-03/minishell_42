/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 22:38:43 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/26 19:01:52 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	tlen;

	if (!s1 || !s2)
	{
		if (!s1 || !*s1)
			return (s2);
		if (!s2 || !*s2)
			return (s1);
	}
	tlen = ft_strlen(s1) + ft_strlen(s2);
	str = malloc ((tlen + 1) * sizeof(char));
	if (!str)
	{
		free(s1);
		s1 = NULL;
		return (0);
	}
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str + ft_strlen (s1), s2, tlen + 1);
	free(s1);
	s1 = NULL;
	free(s2);
	s2 = NULL;
	return (str);
}

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*str;
// 	int		join_len;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	if (!*s2)
// 		return (s1);
// 	else
// 	join_len = ft_strlen(s1) + ft_strlen(s2);
// 	str = ft_calloc((join_len + 1), 1);
// 	if (!str)
// 	{
// 		ft_free(&s1, NULL);
// 		return (NULL);
// 	}
// 	while (s1 && s1[i])
// 		str[i++] = s1[j++];
// 	ft_free(&s1, NULL);
// 	j = 0;
// 	while (s2[j])
// 		str[i++] = s2[j++];
// 	return (str);
// }
