/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 12:08:04 by rmarzouk          #+#    #+#             */
/*   Updated: 2023/12/27 22:19:51 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *s, char c)
{
	size_t	nbr;

	nbr = 0;
	while (*s)
	{
		while (*s == c)
		{
			s++;
			if (*s == '\0')
				return (nbr);
		}
		while (*s && *s != c)
			s++;
		nbr++;
	}
	return (nbr);
}

static size_t	word_len(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (*(s + i) && *(s + i) != c)
		i++;
	return (i);
}

static void	freef(char **array, size_t i)
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		free(*(array + j));
		j++;
	}
	free(array);
}

static char	**ft_result(char **res, const char *s, char c, size_t words)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (j < words)
	{
		while (*(s + i) == c)
			i++;
		*(res + j) = ft_substr(s, i, word_len((s + i), c));
		if (!(*(res + j)))
		{
			freef(res, j);
			return (NULL);
		}
		while (*(s + i) && *(s + i) != c)
			i++;
		j++;
	}
	*(res + j) = 0;
	return (res);
}

char	**ft_split(const char *s, char c)
{
	char	**res;
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	res = (char **)malloc((words + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	res = ft_result(res, s, c, words);
	return (res);
}

/*int main(void)
{
	char str[] = "hello from this country";
	char **res = ft_split(str, ' ');
	int i = 0;
	while (res[i])
	{
		printf("%s\n", res[i]);
		i++;
	}
	return (0);
}*/
