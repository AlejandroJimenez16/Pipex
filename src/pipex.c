/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:53:38 by alejandj          #+#    #+#             */
/*   Updated: 2025/05/05 16:51:04 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process_1(t_pipex *pipex)
{
	pipex->process1 = fork();
	if (pipex->process1 == -1)
		print_errors("ERROR: creating process1", pipex->outfile);
	else if (pipex->process1 == 0)
	{
		close(pipex->pipefd[0]);
		if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
			print_errors("ERROR: dup2 process1 (stdin)", pipex->outfile);
		if (dup2(pipex->pipefd[1], STDOUT_FILENO) == -1)
			print_errors("ERROR: dup2 process1 (stdout)", pipex->outfile);
		execute_commands(pipex->env, pipex->cmd1, pipex->outfile);
	}
}

void	child_process_2(t_pipex *pipex)
{
	pipex->process2 = fork();
	if (pipex->process2 == -1)
		print_errors("Error creating process2", pipex->outfile);
	else if (pipex->process2 == 0)
	{
		close(pipex->pipefd[1]);
		if (dup2(pipex->pipefd[0], STDIN_FILENO) == -1)
			print_errors("ERROR: dup2 process2 (stdin)", pipex->outfile);
		if (dup2(pipex->fd_out, STDOUT_FILENO) == -1)
			print_errors("ERROR: dup2 process2 (stdout)", pipex->outfile);
		execute_commands(pipex->env, pipex->cmd2, pipex->outfile);
	}
}

void	cleanup(t_pipex *pipex)
{
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	waitpid(pipex->process1, NULL, 0);
	waitpid(pipex->process2, NULL, 0);
	free_arr(pipex->cmd1);
	free_arr(pipex->cmd2);
}

void	init_fds(int *fd_in, int *fd_out, char *infile, char *outfile)
{
	*fd_in = open(infile, O_RDONLY);
	*fd_out = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*fd_in < 0)
		print_errors("ERROR: opening infile", outfile);
	if (*fd_out < 0)
		print_errors("ERROR: opening outfile", outfile);
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;
	int		pipe_status;

	if (argc == 5)
	{
		pipex.env = env;
		pipex.outfile = argv[4];
		init_fds(&pipex.fd_in, &pipex.fd_out, argv[1], argv[4]);
		pipex.cmd1 = ft_split(argv[2], ' ');
		if (!pipex.cmd1)
			print_errors("ERROR: parsing command 1", pipex.outfile);
		pipex.cmd2 = ft_split(argv[3], ' ');
		if (!pipex.cmd2)
			print_errors("ERROR: parsing command 2", pipex.outfile);
		pipe_status = pipe(pipex.pipefd);
		if (pipe_status == -1)
			print_errors("ERROR: creating pipe", pipex.outfile);
		child_process_1(&pipex);
		child_process_2(&pipex);
		cleanup(&pipex);
	}
	else
		fail_args();
}
