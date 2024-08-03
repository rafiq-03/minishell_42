/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:31:21 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/08/03 17:07:08 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// pwd buitin implementation
extern int g_exit_status;
int	mini_pwd()
{
	char *buffer;

	buffer = getcwd(NULL, 0);
    if (buffer)
        printf("%s\n", buffer);
    else
	{
        perror("Error");
		g_exit_status = 126;
		return (126);
	}
	free(buffer);
	g_exit_status = EXIT_SUCCESS;
	return (EXIT_SUCCESS);
}
