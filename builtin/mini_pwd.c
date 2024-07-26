/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:31:21 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/26 16:52:22 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// pwd buitin implementation
int	mini_pwd()
{
	char *buffer;

	buffer = getcwd(NULL, 0);
    if (buffer)
        printf("%s\n", buffer);
    else
	{
        perror("Error");
		return (1);
	}
	free(buffer);
	return (0);
}
