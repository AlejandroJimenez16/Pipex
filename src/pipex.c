/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:53:38 by alejandj          #+#    #+#             */
/*   Updated: 2025/05/04 14:37:08 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	execute_commands(char *env[], char **cmd)
{
	char	**arr_path;
	int		arr_path_id;
	char	*path;
	char	*temp;

	path = ft_strdup("");
	arr_path = get_path_cmd(env);
	arr_path_id = 0;
	while (arr_path[arr_path_id] != NULL)
	{
		temp = ft_strjoin(arr_path[arr_path_id], "/");
		path = ft_strjoin(temp, cmd[0]);
		if (access(path, X_OK) == 0)
		{
			if (execve(path, cmd, env) == -1)
				print_errors("ERROR: execve process1");
			break ;
		}
		else
			arr_path_id++;
	}
}

void	child_process_1(t_pipex *pipex)
{
	pipex->process1 = fork();
	if (pipex->process1 == -1)
		print_errors("ERROR: creating process1");
	else if (pipex->process1 == 0)
	{
		close(pipex->pipefd[0]);
		if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
			print_errors("ERROR: dup2 process1 (stdin)");
		if (dup2(pipex->pipefd[1], STDOUT_FILENO) == -1)
			print_errors("ERROR: dup2 process1 (stdout)");
		execute_commands(pipex->env, pipex->cmd1);
	}
}

void	child_process_2(t_pipex *pipex)
{
	pipex->process2 = fork();
	if (pipex->process2 == -1)
		print_errors("Error creating process2");
	else if (pipex->process2 == 0)
	{
		close(pipex->pipefd[1]);
		if (dup2(pipex->pipefd[0], STDIN_FILENO) == -1)
			print_errors("ERROR: dup2 process2 (stdin)");
		if (dup2(pipex->fd_out, STDOUT_FILENO) == -1)
			print_errors("ERROR: dup2 process2 (stdout)");
		execute_commands(pipex->env, pipex->cmd2);
	}
}

void	init_fds(int *fd_in, int *fd_out, char *infile, char *outfile)
{
	*fd_in = open(infile, O_RDONLY);
	*fd_out = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*fd_in < 0)
		print_errors("ERROR: opening infile");
	if (*fd_out < 0)
		print_errors("ERROR: opening outfile");
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex pipex;
	int		pipe_status;

	if (argc == 5)
	{
		pipex.env = env;
		init_fds(&pipex.fd_in, &pipex.fd_out, argv[1], argv[4]);
		pipex.cmd1 = ft_split(argv[2], ' ');
		if (!pipex.cmd1)
			print_errors("ERROR: parsing command 1");
		pipex.cmd2 = ft_split(argv[3], ' ');
		if (!pipex.cmd2)
			print_errors("ERROR: parsing command 2");
		pipe_status = pipe(pipex.pipefd);
		if (pipe_status == -1)
			print_errors("ERROR: creating pipe");
		child_process_1(&pipex);
		child_process_2(&pipex);
		close(pipex.pipefd[0]);
		close(pipex.pipefd[1]);
		waitpid(pipex.process1, NULL, 0);
		waitpid(pipex.process2, NULL, 0);
		free_arr(pipex.cmd1);
		free_arr(pipex.cmd2);
	}
	else
	{
		ft_putstr_fd("\033[1;31mERROR ARGUMENTS\033[0m\n", 2);
		ft_putstr_fd("\033[1;33mARGS FORMAT: ./pipex infile 'cmd1' 'cmd2' outfile\033[0m\n", 2);
		return (1);
	}
}
