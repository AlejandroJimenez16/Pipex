/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:32:34 by alejandj          #+#    #+#             */
/*   Updated: 2025/05/24 01:05:09 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		fd_in;
	int		fd_out;
	int		pipefd[2];
	char	**cmd1;
	char	**cmd2;
	char	*outfile;
	char	**env;
	pid_t	process1;
	pid_t	process2;
}			t_pipex;

void		free_arr(char **arr);
void		print_errors(char *error, char *outfile);
void		print_cmd_error(char *cmd, char *outfile);
void		fail_args(void);
char		**get_path_cmd(char *env[]);
void		execute_commands(char *env[], char **cmd, char *outfile);

#endif
