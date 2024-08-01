/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:31:21 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/08/01 08:51:47 by mskhairi         ###   ########.fr       */
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
		exit_status = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	free(buffer);
	exit_status = EXIT_SUCCESS;
	return (EXIT_SUCCESS);
}
