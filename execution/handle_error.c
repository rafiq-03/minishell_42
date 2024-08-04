/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:36:05 by mskhairi          #+#    #+#             */
/*   Updated: 2024/08/04 13:01:36 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern int g_exit_status;
// void handle_access_error(const char *cmd) {
//     if (errno == EACCES) {
//         fprintf(stderr, "%s: Permission denied\n", cmd);
//         exit(126);
//     } else if (errno == ENOENT) {
//         fprintf(stderr, "%s: No such file or directory\n", cmd);
//         exit(127);
//     } else if (errno == ENOTDIR) {
//         fprintf(stderr, "%s: Not a directory\n", cmd);
//         exit(127);
//     } else if (errno == EFAULT) {
//         fprintf(stderr, "%s: Bad address\n", cmd);
//         exit(1);
//     } else if (errno == ELOOP) {
//         fprintf(stderr, "%s: Too many symbolic links encountered\n", cmd);
//         exit(1);
//     } else if (errno == ENAMETOOLONG) {
//         fprintf(stderr, "%s: File name too long\n", cmd);
//         exit(1);
//     } else if (errno == EROFS) {
//         fprintf(stderr, "%s: Read-only file system\n", cmd);
//         exit(126);
//     } else {
//         fprintf(stderr, "%s: Error: %s\n", cmd, strerror(errno));
//         exit(1);
//     }
// }

void    print_error(char *cmd, char *error)
{
    ft_putstr_fd("minishell : ", 2);
    ft_putstr_fd(cmd, 2);
    ft_putstr_fd(error, 2);
}


void handle_errors(char *cmd, bool is_path)
{
    struct stat cmd_info;
    int flag;

    flag = stat(cmd, &cmd_info);
 	if (flag != -1)
    {
        if (S_ISDIR(cmd_info.st_mode))
        {
            print_error(cmd, ": is a directory\n");
            exit(126);
        }
        else if (!(cmd_info.st_mode & S_IXUSR))
        {
            print_error(cmd, ": Permission denied\n");
            exit(126);
        } 
        else
        {
            print_error(cmd, " command not found\n");
            exit(127);
        }
    }
	else {
        if (!is_path)
        {
            print_error(cmd, ": command not found\n");    
            exit(127);
        }
		if (errno == ENOENT){
			print_error(cmd, ": No such file or directory\n");
			exit(127);
		} else {
			perror(cmd);
			exit(126);
		}
    }
}
