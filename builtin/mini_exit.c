/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:15:02 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/08/03 17:07:08 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int g_exit_status;
int is_number(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '-' || str[i] == '+')
		return (0);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

int check_args(char **cmd)
{
	//chech if !cmd[1] ==> exit(0);
	if (!cmd[1])
		exit(0);
	//chech if num_of cmd > 2 ==> print too many args  ==> exit(check exit status in bash);
	if (is_number(cmd[1]))
	{
		dprintf(2, " numeric argument required\n");//check the behavior of bash
		exit(255);// exit(check exit status in bash);
	}
	if (cmd[1] && cmd[2])
	{
		dprintf(2, " too many arguments\n");
		g_exit_status = EXIT_FAILURE;
		return(EXIT_FAILURE);// exit(check exit status in bash);
	}
	// check if is_number(cmd[i]) else ==> print arg is not numeric ==> exit(check exit status in bash) ;
	return (0);
}

int	mini_exit(char **cmd)
{
	int check_errors;
	//free(everything that we should be freeing)
	printf("exit\n");
	check_errors = check_args(cmd);
	if (check_errors)
		return(1);
	g_exit_status  = ft_atoi(cmd[1]);
	exit(g_exit_status);
	return (0);//optionally , to giving the OS all informations about the process through the return value
}
