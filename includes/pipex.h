/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:32:34 by alejandj          #+#    #+#             */
/*   Updated: 2025/05/04 14:22:19 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>

typedef struct s_pipex
{
    int		fd_in;
    int		fd_out;
    int		pipefd[2];
	char	**cmd1;
	char	**cmd2;
	char	**env;
	pid_t	process1;
	pid_t	process2;
} t_pipex;


void	free_arr(char **arr);
void	print_errors(char *error);
char	**get_path_cmd(char *env[]);

#endif
