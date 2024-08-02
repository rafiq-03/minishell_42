/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:31:21 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/08/02 10:25:51 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// pwd buitin implementation
extern int exit_status;
int	mini_pwd()
{
	char *buffer;

	buffer = getcwd(NULL, 0);
    if (buffer)
        printf("%s\n", buffer);
    else
	{
        perror("Error");
		exit_status = 126;
		return (126);
	}
	free(buffer);
	exit_status = EXIT_SUCCESS;
	return (EXIT_SUCCESS);
}
