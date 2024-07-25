/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:31:21 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/07/25 16:23:11 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// pwd buitin implementation
int	mini_pwd()
{
	char *buffer;
	
	buffer = getcwd(NULL, 0);
	if (!buffer)
		printf ("error\n");
	printf("%s\n", buffer);
	return (0);
}
