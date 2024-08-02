/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:36:05 by mskhairi          #+#    #+#             */
/*   Updated: 2024/08/02 11:54:06 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern int exit_status;
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

void handle_errors(const char *cmd, int flag)
{
    struct stat statbuf;
 
 	if (flag != -1) {
        if (S_ISDIR(statbuf.st_mode)) {
            fprintf(stderr, "%s: is a directory\n", cmd);
            exit(126);
        } else if (!(statbuf.st_mode & S_IXUSR)) {
            fprintf(stderr, "%s: Permission denied\n", cmd);
            exit(126);
        } else {
            fprintf(stderr, "%s: command not found\n", cmd);
            exit(127);
        }
    }
	else {
		if (errno == ENOENT){
			fprintf(stderr, "%s: No such file or directory\n", cmd);
			exit(127);
		} else {
			perror(cmd);
			exit(126);
		}
    }
}